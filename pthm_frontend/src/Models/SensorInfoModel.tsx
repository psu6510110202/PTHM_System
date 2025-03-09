export default interface SensorInfoModel {
    patient_id: string;
    heart_rate: number;
    blood_oxy: number;
    body_temp: number;
    room_temp: number;
    room_humidity: number;
    updatedAt: Date;
    camera: string;
}