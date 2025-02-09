import { PatientDashboardRepository, PatientInfoRepository } from "./PatientRepository/PatientRepository";
import { SensorRepository } from "./SensorRepository/SensorRepository";

const repositories = {
    PatientDashboardRepository: new PatientDashboardRepository(),
    PatientInfoRepository : new PatientInfoRepository(),
    SensorRepository: new SensorRepository()
}

export default repositories;