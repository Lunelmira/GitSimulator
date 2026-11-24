
#include "VirtualFS.hpp"
#include "GitException.hpp"
#include <iostream>
#include <algorithm>

VirtualFS::VirtualFS() {
    root = Directory("/");
    currentPath = "/";
}

std::string VirtualFS::getCurrentPath() const {
    return currentPath;
}

void VirtualFS::changeDirectory(std::string path) {
    std::vector<std::string> parts;

    // اگر مسیر نسبی باشد، از مسیر فعلی شروع می‌کنیم.
    if (path.empty() || path[0] != '/') {
        size_t start = 0;

        while (start < currentPath.length()) {
            size_t end = currentPath.find('/', start);

            if (end == std::string::npos) {
                end = currentPath.length();
            }

            if (end > start) {
                parts.push_back(currentPath.substr(start, end - start));
            }

            start = end + 1;
        }
    }

    // اجزای مسیر ورودی را بررسی می‌کنیم.
    size_t start = 0;

    while (start < path.length()) {
        size_t end = path.find('/', start);

        if (end == std::string::npos) {
            end = path.length();
        }

        std::string part = path.substr(start, end - start);

        if (part == "..") {
            if (!parts.empty()) {
                parts.pop_back();
            }
        }
        else if (part != "" && part != ".") {
            parts.push_back(part);
        }

        start = end + 1;
    }

    // از پوشه اصلی شروع می‌کنیم و مسیر را بررسی می‌کنیم.
    Directory* current = &root;

    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Directory not found: " + parts[i]);
        }
    }

    // مسیر جدید را می‌سازیم.
    currentPath = "/";

    for (size_t i = 0; i < parts.size(); i++) {
        currentPath += parts[i];

        if (i + 1 < parts.size()) {
            currentPath += "/";
        }
    }
}

void VirtualFS::makeDirectory(std::string name) {
    if (name.empty()) {
        throw GitException("Directory name cannot be empty");
    }

    if (name == "." || name == ".." || name.find('/') != std::string::npos) {
        throw GitException("Invalid directory name");
    }

    Directory* current = &root;

    std::vector<std::string> parts;
    size_t start = 0;

    while (start < currentPath.length()) {
        size_t end = currentPath.find('/', start);

        if (end == std::string::npos) {
            end = currentPath.length();
        }

        if (end > start) {
            parts.push_back(currentPath.substr(start, end - start));
        }

        start = end + 1;
    }

    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Current directory does not exist");
        }
    }

    if (current->hasDirectory(name) || current->hasFile(name)) {
        throw GitException("A file or directory with this name already exists");
    }

    current->addDirectory(Directory(name));
}

void VirtualFS::createFile(std::string name) {
    if (name.empty()) {
        throw GitException("File name cannot be empty");
    }

    if (name == "." || name == ".." || name.find('/') != std::string::npos) {
        throw GitException("Invalid file name");
    }

    Directory* current = &root;

    std::vector<std::string> parts;
    size_t start = 0;

    while (start < currentPath.length()) {
        size_t end = currentPath.find('/', start);

        if (end == std::string::npos) {
            end = currentPath.length();
        }

        if (end > start) {
            parts.push_back(currentPath.substr(start, end - start));
        }

        start = end + 1;
    }

    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Current directory does not exist");
        }
    }

    if (current->hasFile(name) || current->hasDirectory(name)) {
        throw GitException("A file or directory with this name already exists");
    }

    current->addFile(File(name, std::vector<std::string>()));
}

void VirtualFS::removeFile(std::string name) {
    if (name.empty()) {
        throw GitException("File name cannot be empty");
    }

    if (name == "." || name == ".." || name.find('/') != std::string::npos) {
        throw GitException("Invalid file name");
    }

    Directory* current = &root;

    std::vector<std::string> parts;
    size_t start = 0;

    while (start < currentPath.length()) {
        size_t end = currentPath.find('/', start);

        if (end == std::string::npos) {
            end = currentPath.length();
        }

        if (end > start) {
            parts.push_back(currentPath.substr(start, end - start));
        }

        start = end + 1;
    }

    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Current directory does not exist");
        }
    }

    std::vector<File>& files = current->getFiles();

    bool found = false;

    for (size_t i = 0; i < files.size(); i++) {
        if (files[i].getPath() == name) {
            files.erase(files.begin() + i);
            found = true;
            break;
        }
    }

    if (!found) {
        throw GitException("File not found: " + name);
    }
}

void VirtualFS::removeDirectory(std::string name) {
    if (name.empty()) {
        throw GitException("Directory name cannot be empty");
    }

    if (name == "." || name == ".." || name.find('/') != std::string::npos) {
        throw GitException("Invalid directory name");
    }

    Directory* current = &root;

    std::vector<std::string> parts;
    size_t start = 0;

    while (start < currentPath.length()) {
        size_t end = currentPath.find('/', start);

        if (end == std::string::npos) {
            end = currentPath.length();
        }

        if (end > start) {
            parts.push_back(currentPath.substr(start, end - start));
        }

        start = end + 1;
    }

    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Current directory does not exist");
        }
    }

    std::vector<Directory>& directories = current->getDirectories();

    bool found = false;

    for (size_t i = 0; i < directories.size(); i++) {
        if (directories[i].getName() == name) {
            if (!directories[i].getFiles().empty() ||
                !directories[i].getDirectories().empty()) {
                throw GitException("Directory is not empty");
            }

            directories.erase(directories.begin() + i);
            found = true;
            break;
        }
    }

    if (!found) {
        throw GitException("Directory not found: " + name);
    }
}
void VirtualFS::listContents() {
    Directory* current = &root;

    // استخراج اجزای مسیر فعلی
    std::vector<std::string> parts;
    size_t start = 0;

    while (start < currentPath.length()) {
        size_t end = currentPath.find('/', start);

        if (end == std::string::npos) {
            end = currentPath.length();
        }

        if (end > start) {
            parts.push_back(currentPath.substr(start, end - start));
        }

        start = end + 1;
    }

    // پیدا کردن پوشه فعلی
    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Current directory not found");
        }
    }

    // جمع‌آوری نام پوشه‌ها و فایل‌ها
    std::vector<std::string> names;

    std::vector<Directory>& directories = current->getDirectories();

    for (size_t i = 0; i < directories.size(); i++) {
        names.push_back(directories[i].getName() + "/");
    }

    std::vector<File>& files = current->getFiles();

    for (size_t i = 0; i < files.size(); i++) {
        names.push_back(files[i].getPath());
    }

    // مرتب‌سازی نام‌ها
    std::sort(names.begin(), names.end());

    // نمایش محتویات
    for (size_t i = 0; i < names.size(); i++) {
        std::cout << names[i] << std::endl;
    }
}
void VirtualFS::displayFile(std::string name) {
    if (name.empty()) {
        throw GitException("File name cannot be empty");
    }

    if (name == "." || name == ".." || name.find('/') != std::string::npos) {
        throw GitException("Invalid file name");
    }

    Directory* current = &root;

    // استخراج اجزای مسیر فعلی
    std::vector<std::string> parts;
    size_t start = 0;

    while (start < currentPath.length()) {
        size_t end = currentPath.find('/', start);

        if (end == std::string::npos) {
            end = currentPath.length();
        }

        if (end > start) {
            parts.push_back(currentPath.substr(start, end - start));
        }

        start = end + 1;
    }

    // پیدا کردن پوشه فعلی
    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Current directory not found");
        }
    }

    // پیدا کردن فایل و نمایش محتوای آن
    std::vector<File>& files = current->getFiles();

    for (size_t i = 0; i < files.size(); i++) {
        if (files[i].getPath() == name) {
            std::vector<std::string> content = files[i].getContent();

            for (size_t j = 0; j < content.size(); j++) {
                std::cout << content[j] << std::endl;
            }

            return;
        }
    }

    throw GitException("File not found: " + name);
}
void VirtualFS::writeFile(std::string name, std::vector<std::string> content) {
    if (name.empty()) {
        throw GitException("File name cannot be empty");
    }

    if (name == "." || name == ".." || name.find('/') != std::string::npos) {
        throw GitException("Invalid file name");
    }

    Directory* current = &root;

    std::vector<std::string> parts;
    size_t start = 0;

    while (start < currentPath.length()) {
        size_t end = currentPath.find('/', start);

        if (end == std::string::npos) {
            end = currentPath.length();
        }

        if (end > start) {
            parts.push_back(currentPath.substr(start, end - start));
        }

        start = end + 1;
    }

    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Current directory not found");
        }
    }

    std::vector<File>& files = current->getFiles();

    for (size_t i = 0; i < files.size(); i++) {
        if (files[i].getPath() == name) {
            files[i].setContent(content);
            return;
        }
    }

    throw GitException("File not found: " + name);
}
void VirtualFS::appendFile(std::string name, std::string line) {
    if (name.empty()) {
        throw GitException("File name cannot be empty");
    }

    if (name == "." || name == ".." || name.find('/') != std::string::npos) {
        throw GitException("Invalid file name");
    }

    Directory* current = &root;

    std::vector<std::string> parts;
    size_t start = 0;

    while (start < currentPath.length()) {
        size_t end = currentPath.find('/', start);

        if (end == std::string::npos) {
            end = currentPath.length();
        }

        if (end > start) {
            parts.push_back(currentPath.substr(start, end - start));
        }

        start = end + 1;
    }

    for (size_t i = 0; i < parts.size(); i++) {
        bool found = false;

        std::vector<Directory>& directories = current->getDirectories();

        for (size_t j = 0; j < directories.size(); j++) {
            if (directories[j].getName() == parts[i]) {
                current = &directories[j];
                found = true;
                break;
            }
        }

        if (!found) {
            throw GitException("Current directory not found");
        }
    }

    std::vector<File>& files = current->getFiles();

    for (size_t i = 0; i < files.size(); i++) {
        if (files[i].getPath() == name) {
            files[i].appendLine(line);
            return;
        }
    }

    throw GitException("File not found: " + name);
}
void VirtualFS::collectSnapshots(
    const Directory& directory,
    std::string path,
    std::vector<FileSnapshot>& snapshots
) const {

    // جمع‌آوری فایل‌های پوشه فعلی
    const std::vector<File>& files = directory.getFiles();

    for (size_t i = 0; i < files.size(); i++) {

        std::string filePath;

        if (path.empty()) {
            filePath = files[i].getPath();
        }
        else {
            filePath = path + "/" + files[i].getPath();
        }

        snapshots.push_back(files[i].createSnapshot());

        // مسیر کامل فایل را در Snapshot ذخیره می‌کنیم
        snapshots.back() = FileSnapshot(filePath, files[i].getContent());
    }

    // پیمایش پوشه‌های فرزند
    const std::vector<Directory>& directories = directory.getDirectories();

    for (size_t i = 0; i < directories.size(); i++) {

        std::string directoryPath;

        if (path.empty()) {
            directoryPath = directories[i].getName();
        }
        else {
            directoryPath = path + "/" + directories[i].getName();
        }

        collectSnapshots(directories[i], directoryPath, snapshots);
    }
}


std::vector<FileSnapshot> VirtualFS::createSnapshot() const {

    std::vector<FileSnapshot> snapshots;

    collectSnapshots(root, "", snapshots);

    return snapshots;
}
void VirtualFS::restoreSnapshot(std::vector<FileSnapshot> snapshots) {

    // یک فایل‌سیستم جدید می‌سازیم تا در صورت خطا،
    // فایل‌سیستم فعلی دست‌نخورده باقی بماند.
    Directory restoredRoot("/");

    for (size_t i = 0; i < snapshots.size(); i++) {

        std::string path = snapshots[i].getPath();

        if (path.empty() || path[0] == '/') {
            throw GitException("Invalid snapshot path");
        }

        std::vector<std::string> parts;
        size_t start = 0;

        while (start < path.length()) {
            size_t end = path.find('/', start);

            if (end == std::string::npos) {
                end = path.length();
            }

            std::string part = path.substr(start, end - start);

            if (part.empty() || part == "." || part == "..") {
                throw GitException("Invalid snapshot path");
            }

            parts.push_back(part);
            start = end + 1;
        }

        Directory* current = &restoredRoot;

        // ساخت پوشه‌های مسیر
        for (size_t j = 0; j + 1 < parts.size(); j++) {

            if (current->hasFile(parts[j])) {
                throw GitException("File and directory name conflict");
            }

            if (!current->hasDirectory(parts[j])) {
                current->addDirectory(Directory(parts[j]));
            }

            std::vector<Directory>& directories =
                current->getDirectories();

            for (size_t k = 0; k < directories.size(); k++) {
                if (directories[k].getName() == parts[j]) {
                    current = &directories[k];
                    break;
                }
            }
        }

        std::string fileName = parts.back();

        if (current->hasDirectory(fileName) ||
            current->hasFile(fileName)) {
            throw GitException("Duplicate snapshot path");
        }

        // بازیابی فایل و محتوای آن
        File restoredFile(fileName, snapshots[i].getContent());

        current->addFile(restoredFile);
    }

    // جایگزینی فایل‌سیستم قبلی با نسخه بازیابی‌شده
    root = restoredRoot;
    currentPath = "/";
}