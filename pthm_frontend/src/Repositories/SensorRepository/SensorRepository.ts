import { IRepository } from "../IRepository";
import SensorInfoModel from "../../Models/SensorInfoModel";
import conf from "../../conf";

export class SensorRepository implements IRepository<SensorInfoModel> {
    urlPrefix = `${conf.apiPrefix}/api/sensor-devices`;
    
    async getAll(token: string): Promise<SensorInfoModel[] | null> {
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

    async getByPatientId(id: string, token: string): Promise<SensorInfoModel | null> {
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
