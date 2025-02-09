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
}
