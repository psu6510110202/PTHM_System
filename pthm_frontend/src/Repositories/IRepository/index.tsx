export interface IRepository<T> {
    getAll?(token: string): Promise<T[] | null>; // Added `token` parameter
}
