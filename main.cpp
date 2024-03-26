#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <thread>

class File {
protected:
    std::string name;
    std::string extension;
    std::time_t createdTime;
    std::time_t updatedTime;

public:
    File(const std::string& name, const std::string& extension)
        : name(name), extension(extension) {
        createdTime = std::time(nullptr);
        updatedTime = createdTime;
    }

    virtual ~File() {}

    virtual void update() {
        updatedTime = std::time(nullptr);
    }

    const std::string& getName() const {
        return name;
    }

    const std::string& getExtension() const {
        return extension;
    }

    std::time_t getUpdatedTime() const {
        return updatedTime;
    }
};

class FileManager {
private:
    std::vector<File*> files;
    std::time_t lastSnapshotTime;

public:
    FileManager() : lastSnapshotTime(std::time(nullptr)) {}

    ~FileManager() {
        for (auto file : files) {
            delete file;
        }
        files.clear();
    }

    void addFile(File* file) {
        files.push_back(file);
    }

    void printStatus() {
        std::time_t currentTime = std::time(nullptr);
        std::cout << "Snapshot time: " << std::put_time(std::localtime(&lastSnapshotTime), "%Y-%m-%d %H:%M:%S") << "\n";
        for (auto file : files) {
            std::cout << file->getName() << "." << file->getExtension() << " ";
            if (file->getUpdatedTime() > lastSnapshotTime) {
                std::cout << "changed\n";
            } else {
                std::cout << "no change\n";
            }
        }
        lastSnapshotTime = currentTime;
    }

    void detectChanges() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            for (auto file : files) {
                file->update();
            }
            printStatus();
        }
    }
};

int main() {
    FileManager fileManager;

    fileManager.addFile(new File("test", "txt"));
    fileManager.addFile(new File("image", "png"));
    fileManager.addFile(new File("python_script", "py"));

    std::thread detectionThread(&FileManager::detectChanges, &fileManager);

    fileManager.printStatus();

    detectionThread.join();

    return 0;
}
