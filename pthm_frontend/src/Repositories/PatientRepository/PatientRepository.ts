import { IRepository } from "../IRepository";
import PatientDashboard from "../../Models/PatientDashboard";
import conf from "../../conf";
import PatientInfoModel from "../../Models/PatientInfoModel";

export class PatientDashboardRepository implements IRepository<PatientDashboard> {
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

export class PatientSeachRepository implements IRepository<PatientInfoModel> {
    urlPrefix = `${conf.apiPrefix}/api/patient-datas`;
    
    async getAll(token: string): Promise<PatientInfoModel[] | null> {
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