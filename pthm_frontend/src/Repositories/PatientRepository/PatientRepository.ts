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

export class PatientInfoRepository implements IRepository<PatientInfoModel> {
    urlPrefix = `${conf.apiPrefix}/api/patient-datas`;

    // Fetch all patients
    async getAll(token: string): Promise<PatientInfoModel[] | null> {
        try {
            const response = await fetch(this.urlPrefix, {
                method: "GET",
                headers: {
                    "Authorization": `Bearer ${token}`,
                    "Accept": "application/json",
                    "Content-Type": "application/json"
                },
            });

            if (!response.ok) {
                throw new Error(`Error ${response.status}: ${response.statusText}`);
            }

            const responseData = await response.json();
            return responseData?.data ?? []; // Ensure always returning an array
        } catch (error) {
            console.error("Failed to fetch patient data:", error);
            return null;
        }
    }

    // Fetch patient by ID
    async getById(id: string, token: string): Promise<PatientInfoModel | null> {
        try {
            const encodedId = encodeURIComponent(id); // Encode ID for safety
            const response = await fetch(`${this.urlPrefix}?filters[patient_id][$eq]=${encodedId}`, {
                method: "GET",
                headers: {
                    "Authorization": `Bearer ${token}`,
                    "Accept": "application/json",
                    "Content-Type": "application/json"
                },
            });

            if (!response.ok) {
                throw new Error(`Error ${response.status}: ${response.statusText}`);
            }

            const responseData = await response.json();
            const patients = responseData?.data ?? []; // Ensure an array is returned

            if (patients.length === 0) {
                console.warn(`No patient found with ID: ${id}`);
                return null;
            }

            return patients[0]; // Return the first matching patient
        } catch (error) {
            console.error(`Failed to fetch patient data for ID ${id}:`, error);
            return null;
        }
    }
}
