import { PatientRepository } from "./PatientRepository/PatientRepository";
import { SensorRepository } from "./SensorRepository/SensorRepository";

const repositories = {
    PatientRepository: new PatientRepository(),
    SensorRepository: new SensorRepository()
}

export default repositories;