class Better_Possession_Driver : public Driver_t {
private:
    int calculatePossession(Grid_t *grid, Turn_t test);
    void swap(int *a, int *b);
    virtual void parallelSort(int *comparer, int *latched, int size);

public:
    Turn_t steer(Grid_t *grid);
};
