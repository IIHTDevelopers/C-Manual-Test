#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char sensorId[10];
    bool status;
} Sensor;

typedef struct {
    Sensor* sensors[10];
    int sensorCount;
} DoorSensorManagementService;

typedef struct {
    char vehicleId[10];
    bool engineStatus;
} VehicleParameters;

typedef struct {
    VehicleParameters parameters[10];
    int parameterCount;
} VehicleParametersRepository;

typedef struct {
    Sensor* sensors[10];
    int sensorCount;
    char alerts[10][100];
    int alertCount;
    VehicleParametersRepository* vehicleParameters;
} CentralLockingSystem;

typedef struct {
    CentralLockingSystem* lockingSystem;
} UserInterfaceController;

void Sensor_init(Sensor* sensor, const char* sensorId) {
    strcpy(sensor->sensorId, sensorId);
    sensor->status = false;
}

bool Sensor_getStatus(Sensor* sensor) {
    return sensor->status;
}

void Sensor_setStatus(Sensor* sensor, bool status) {
    sensor->status = status;
}

void DoorSensorManagementService_init(DoorSensorManagementService* service) {
    service->sensorCount = 0;
}

void DoorSensorManagementService_activateSensor(DoorSensorManagementService* service, const char* sensorId) {
    for (int i = 0; i < service->sensorCount; i++) {
        if (strcmp(service->sensors[i]->sensorId, sensorId) == 0) {
            Sensor_setStatus(service->sensors[i], true);
            return;
        }
    }
    printf("Sensor %s not found.\n", sensorId);
}

void DoorSensorManagementService_deactivateSensor(DoorSensorManagementService* service, const char* sensorId) {
    for (int i = 0; i < service->sensorCount; i++) {
        if (strcmp(service->sensors[i]->sensorId, sensorId) == 0) {
            Sensor_setStatus(service->sensors[i], false);
            return;
        }
    }
    printf("Sensor %s not found.\n", sensorId);
}

bool DoorSensorManagementService_checkSensorStatus(DoorSensorManagementService* service, const char* sensorId) {
    for (int i = 0; i < service->sensorCount; i++) {
        if (strcmp(service->sensors[i]->sensorId, sensorId) == 0) {
            return Sensor_getStatus(service->sensors[i]);
        }
    }
    printf("Sensor %s not found.\n", sensorId);
    return false;
}

void DoorSensorManagementService_addSensor(DoorSensorManagementService* service, Sensor* sensor) {
    service->sensors[service->sensorCount++] = sensor;
}

void CentralLockingSystem_init(CentralLockingSystem* system) {
    system->sensorCount = 0;
    system->alertCount = 0;
    system->vehicleParameters = NULL;
}

void CentralLockingSystem_lockAllDoors(CentralLockingSystem* system) {
    for (int i = 0; i < system->sensorCount; i++) {
        Sensor_setStatus(system->sensors[i], true);
    }
    printf("All doors locked.\n");
}

void CentralLockingSystem_unlockAllDoors(CentralLockingSystem* system) {
    for (int i = 0; i < system->sensorCount; i++) {
        Sensor_setStatus(system->sensors[i], false);
    }
    printf("All doors unlocked.\n");
}

void CentralLockingSystem_lockSingleDoor(CentralLockingSystem* system, const char* doorId) {
    for (int i = 0; i < system->sensorCount; i++) {
        if (strcmp(system->sensors[i]->sensorId, doorId) == 0) {
            Sensor_setStatus(system->sensors[i], true);
            printf("Door %s locked.\n", doorId);
            return;
        }
    }
    printf("Door %s not found.\n", doorId);
}

void CentralLockingSystem_unlockSingleDoor(CentralLockingSystem* system, const char* doorId) {
    for (int i = 0; i < system->sensorCount; i++) {
        if (strcmp(system->sensors[i]->sensorId, doorId) == 0) {
            Sensor_setStatus(system->sensors[i], false);
            printf("Door %s unlocked.\n", doorId);
            return;
        }
    }
    printf("Door %s not found.\n", doorId);
}

bool CentralLockingSystem_analyzeLockStatus(CentralLockingSystem* system) {
    for (int i = 0; i < system->sensorCount; i++) {
        if (!Sensor_getStatus(system->sensors[i])) {
            return false;
        }
    }
    return true;
}

void CentralLockingSystem_generateAlerts(CentralLockingSystem* system) {
    if (system->vehicleParameters->parameters[0].engineStatus && !CentralLockingSystem_analyzeLockStatus(system)) {
        strcpy(system->alerts[system->alertCount++], "Warning: Engine started but doors are not locked!");
        printf("Warning: Engine started but doors are not locked!\n");
    }
}

void VehicleParametersRepository_init(VehicleParametersRepository* repository) {
    repository->parameterCount = 0;
}

void VehicleParametersRepository_updateParameters(VehicleParametersRepository* repository, const char* vehicleId, bool engineStatus) {
    strcpy(repository->parameters[repository->parameterCount].vehicleId, vehicleId);
    repository->parameters[repository->parameterCount].engineStatus = engineStatus;
    repository->parameterCount++;
}

bool VehicleParametersRepository_getEngineStatus(VehicleParametersRepository* repository) {
    for (int i = 0; i < repository->parameterCount; i++) {
        return repository->parameters[i].engineStatus;
    }
    return false;
}

void UserInterfaceService_displayMenu() {
    printf(" 0. Quit.\n");
    printf(" 1. Lock all doors.\n");
    printf(" 2. Unlock all doors.\n");
    printf(" 3. Lock single door.\n");
    printf(" 4. Unlock single door.\n");
    printf(" 5. Check lock status.\n");
    printf(" 6. Generate alerts.\n");
}

void UserInterfaceService_displayLockStatus(bool status) {
    printf(status ? "All doors are locked.\n" : "Not all doors are locked.\n");
}

void UserInterfaceService_displaySystemAlerts(char alerts[10][100], int alertCount) {
    if (alertCount > 0) {
        printf("System Alerts:\n");
        for (int i = 0; i < alertCount; i++) {
            printf("%s\n", alerts[i]);
        }
    } else {
        printf("No alerts.\n");
    }
}

void UserInterfaceController_init(UserInterfaceController* controller, CentralLockingSystem* lockingSystem) {
    controller->lockingSystem = lockingSystem;
}

void UserInterfaceController_displayMenu(UserInterfaceController* controller) {
    UserInterfaceService_displayMenu();
}

bool UserInterfaceController_processUserInput(UserInterfaceController* controller, const char* choice) {
    if (strcmp(choice, "0") == 0) {
        printf("Exiting program.\n");
        return false;
    } else if (strcmp(choice, "1") == 0) {
        CentralLockingSystem_lockAllDoors(controller->lockingSystem);
    } else if (strcmp(choice, "2") == 0) {
        CentralLockingSystem_unlockAllDoors(controller->lockingSystem);
    } else if (strcmp(choice, "3") == 0) {
        char doorId[10];
        printf("Enter the door ID to lock: ");
        scanf("%s", doorId);
        CentralLockingSystem_lockSingleDoor(controller->lockingSystem, doorId);
    } else if (strcmp(choice, "4") == 0) {
        char doorId[10];
        printf("Enter the door ID to unlock: ");
        scanf("%s", doorId);
        CentralLockingSystem_unlockSingleDoor(controller->lockingSystem, doorId);
    } else if (strcmp(choice, "5") == 0) {
        bool status = CentralLockingSystem_analyzeLockStatus(controller->lockingSystem);
        UserInterfaceService_displayLockStatus(status);
    } else if (strcmp(choice, "6") == 0) {
        CentralLockingSystem_generateAlerts(controller->lockingSystem);
        UserInterfaceService_displaySystemAlerts(controller->lockingSystem->alerts, controller->lockingSystem->alertCount);
    } else {
        printf("Invalid choice. Please try again.\n");
    }
    return true;
}

int main() {
    VehicleParametersRepository vehicleParams;
    VehicleParametersRepository_init(&vehicleParams);
    VehicleParametersRepository_updateParameters(&vehicleParams, "VH001", false);

    DoorSensorManagementService doorSensorManagement;
    DoorSensorManagementService_init(&doorSensorManagement);

    CentralLockingSystem centralLockingSystem;
    CentralLockingSystem_init(&centralLockingSystem);
    centralLockingSystem.vehicleParameters = &vehicleParams;

    UserInterfaceController uiController;
    UserInterfaceController_init(&uiController, &centralLockingSystem);

    Sensor doorSensor1, doorSensor2, doorSensor3;
    Sensor_init(&doorSensor1, "DS001");
    Sensor_init(&doorSensor2, "DS002");
    Sensor_init(&doorSensor3, "DS003");

    DoorSensorManagementService_addSensor(&doorSensorManagement, &doorSensor1);
    DoorSensorManagementService_addSensor(&doorSensorManagement, &doorSensor2);
    DoorSensorManagementService_addSensor(&doorSensorManagement, &doorSensor3);

    centralLockingSystem.sensors[centralLockingSystem.sensorCount++] = &doorSensor1;
    centralLockingSystem.sensors[centralLockingSystem.sensorCount++] = &doorSensor2;
    centralLockingSystem.sensors[centralLockingSystem.sensorCount++] = &doorSensor3;

    char choice[10];
    while (true) {
        UserInterfaceController_displayMenu(&uiController);
        printf("Enter your choice: ");
        scanf("%s", choice);
        if (!UserInterfaceController_processUserInput(&uiController, choice)) {
            break;
        }
    }
    return 0;
}