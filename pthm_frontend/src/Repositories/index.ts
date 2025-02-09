import { PatientDashboardRepository, PatientSeachRepository } from "./PatientRepository/PatientRepository";
import { SensorRepository } from "./SensorRepository/SensorRepository";

const repositories = {
    PatientDashboardRepository: new PatientDashboardRepository(),
    PatientSeachRepository : new PatientSeachRepository(),
    SensorRepository: new SensorRepository()
}

export default repositories;