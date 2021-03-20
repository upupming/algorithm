class ParkingSystem {
    int cnt[4];

   public:
    ParkingSystem(int b, int m, int s) {
        cnt[1] = b, cnt[2] = m, cnt[3] = s;
    }

    bool addCar(int carType) {
        if (cnt[carType] == 0)
            return false;
        else {
            cnt[carType]--;
            return true;
        }
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
