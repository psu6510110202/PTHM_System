export interface IRepository<T> {
    getAll?(token: string): Promise<T[] | null>; // Added `token` parameter
    getById?(id: string, token: string): Promise<T | null>; // Added `id` and `token` parameters
}
