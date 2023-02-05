#include <atomic>
#include <semaphore.h>
#include <mutex>
using namespace std;

class crb {
    atomic_int32_t count;
    const int32_t n;
    mutex m;
    sem_t turn0{}, turn1{};
public:
    explicit crb(int32_t count): count(count), n(count) {
        sem_init(&turn0, 0, 0);
        sem_init(&turn1, 0, 1);
    }

    crb(const crb&) = delete;

    void sync() {

        m.lock();
        count--;
        if (count == 0) {
            //turn1.acquire();
            sem_wait(&turn1);
            //turn0.release();
            sem_post(&turn0);
        }
        m.unlock();

        //turn0.acquire();
        //turn0.release();
        sem_wait(&turn0);
        sem_post(&turn0);

        m.lock();
        count++;
        if (count == n) {
            //turn0.acquire();
            sem_wait(&turn0);
            //turn1.release();
            sem_post(&turn1);
        }
        m.unlock();

        //turn1.acquire();
        //turn1.release();
        sem_wait(&turn1);
        sem_post(&turn1);
    }
};