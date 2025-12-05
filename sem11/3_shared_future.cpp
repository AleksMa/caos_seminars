#include <future>
#include <thread>
#include <iostream>

using Database = std::string;

std::shared_future<Database&> dbFuture;
std::once_flag initFlag;

std::shared_future<Database&> getDB() {
    std::call_once(initFlag, [&] {
        std::promise<Database&> p;
        dbFuture = p.get_future().share();

        std::cout << "Loading database..." << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        static Database db("SOME BIG DATA");
        p.set_value(db);
    });

    return dbFuture;
}

int main() {
    std::thread t([]() {
        std::cout << "Loaded data from new thread: " << getDB().get() << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Loaded data from main thread: " << getDB().get() << std::endl;

    t.join();
}
