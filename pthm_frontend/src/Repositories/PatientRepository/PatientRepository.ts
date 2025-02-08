import { IRepository } from "../IRepository";
import PatientDashboard from "../../Models/PatientDashboard";
import conf from "../../conf";

export class PatientRepository implements IRepository<PatientDashboard> {
    urlPrefix = `${conf.apiPrefix}/api/patient-datas`;
    
    async getAll(token: string): Promise<PatientDashboard[] | null> {
        try {
            const response = await fetch(this.urlPrefix, {
                method: "GET", // Changed to GET (if the API requires POST, add a body)
                headers: {
                    "Authorization": `Bearer ${token}`,
                    "Accept": "application/json",
                    "Content-Type": "application/json"
                },
            });

            if (!response.ok) {
                throw new Error(`Error ${response.status}: ${response.statusText}`);
            }

            const data = await response.json();
            return data['data'];
        } catch (error) {
            console.error("Failed to fetch patient data:", error);
            return null;
        }
    }
}
