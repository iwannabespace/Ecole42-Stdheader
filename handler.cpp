#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

class FileChooser
{
    public:
        FileChooser(const std::string& extension);
        void execute();
        void set_directory(const std::string& directory);
        size_t size() const;
        const std::string& operator[](size_t index) const;
    private:
        void load_files();
    private:
        std::string directory;
        std::string extension;
        std::vector<std::string> files;
};

FileChooser::FileChooser(const std::string& extension) 
            : extension(extension) 
{ 
}

void FileChooser::execute()
{
    load_files();
}

void FileChooser::set_directory(const std::string& directory)
{
    if (!std::filesystem::exists(directory))
        throw std::string("Directory \"" + directory + "\" does not exist!");
    
    this->directory = directory;
}

size_t FileChooser::size() const
{
    return files.size();
}

const std::string& FileChooser::operator[](size_t index) const
{
    if (index < 0 || index >= files.size())
        throw std::string("Index out of bounds in function FileChooser operator[] for index ") + std::to_string(index);
            
    return files.at(index);
}

void FileChooser::load_files()
{
    auto dir = std::filesystem::directory_iterator(directory);

    for (const auto& file : dir)
    {   
        auto current_file = file.path();

        if (current_file.extension().string() == extension && current_file.filename().string() != __FILE__)
            files.push_back(current_file.string());
    }
}

int set_header(const std::string& filepath);
void execute_work(const std::string& directory, const std::string& extension);

int main(int argc, char** argv)
{
    if (argc == 3)
        execute_work(argv[1], argv[2]);

    else if (argc == 2)
        execute_work(argv[1], ".c");

    else
        execute_work(".", ".c");

    return 0;
}

int set_header(const std::string& filepath)
{
    std::string command = "bash script.sh " + filepath;
    return system(command.c_str());
}

void execute_work(const std::string& directory, const std::string& extension)
{
    FileChooser files(extension);

    try 
    {
        files.set_directory(directory);
    }
    catch (const std::string& error)
    {
        std::cout << error << std::endl;
        exit(1);
    }

    try 
    {
        files.execute();

        for (size_t i = 0; i < files.size(); i++)
        {
            int status = set_header(files[i]);

            if (!status)
                std::cout << files[i] << " now contains a 42 header!" << std::endl;
                
            else
                std::cout << "Something went wrong during setting the 42 header for file \"" << files[i] << "\"!" << std::endl;
        } 
    }    
    catch (const std::string& error)
    {
        std::cout << error << std::endl;
    }
}
