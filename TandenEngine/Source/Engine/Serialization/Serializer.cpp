//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Serializer.h"

namespace TandenEngine {

    const std::string Serializer::mFileBreak  = "=======================\n";

     void Serializer::CreateProject(std::string projectName = "Untitled Project", std::string path = "./") {
        std::cout<<"Creating Project\n";

        //Create Base Project Folder
         if (CreateDirectory((path + "\\" + projectName).c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError())
         {
             // CopyFile(...)
         }
         else
         {
             // Failed to create directory.
             std::cout<<"Error creating base project folder\n";
         }

         //Create Assets Folder
         if (CreateDirectory((path + "\\" + projectName+ "\\Assets").c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError())
         {
             //Populate the assets folder
             std::string folderPath = path + "\\" + projectName + "\\Assets";
         }
         else
         {
             // Failed to create directory.
             std::cout<<"Error creating assets folder\n";
         }

         //Create Project Settings Folder
         if (CreateDirectory((path + "\\" + projectName + "\\ProjectSettings").c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError())
         {
             //Populate the project settings folder
             std::string folderPath = path + "\\" + projectName + "\\ProjectSettings\\";
             //Project file
             {
                 ProjectSettings *projectSettings = new ProjectSettings();
                 //Setup object
                 projectSettings->mProjectName = projectName;

                 //Write to file
                 std::ofstream fileStream;
                 fileStream.open(folderPath + "ProjectSettings" + projectSettings->mExtension);

                 //Write Project settings to file

                 fileStream << projectSettings->mProjectName << "\n";

                 fileStream << mFileBreak;

                 //Resource info

                 for (auto const &resource : projectSettings->mResourceFiles) {

                     fileStream << mFileBreak;
                 }

                 fileStream.close();
             }
         }
         else
         {
             // Failed to create directory.
             std::cout<<"Error creating project settings folder\n";
         }

     }

    ProjectSettings * Serializer::LoadProject(std::string projectDir) {
        std::cout<< "Loading from " << projectDir << std::endl;

        int valid = 1; //Default to true

        DWORD ftyp = GetFileAttributesA(projectDir.c_str());

        if (ftyp == INVALID_FILE_ATTRIBUTES) //Not a valid directory
        {
            valid = 0;
        }
        else if (ftyp & FILE_ATTRIBUTE_DIRECTORY) //Valid Directory
        {
            ftyp = GetFileAttributesA((projectDir + "/Assets/").c_str());
            if (ftyp == INVALID_FILE_ATTRIBUTES) //Not a valid Assets directory
            {
                valid = 0;
            }
            ftyp = GetFileAttributesA((projectDir + "/ProjectSettings/").c_str());
            if (ftyp == INVALID_FILE_ATTRIBUTES) //Not a valid Project settings directory
            {
                valid = 0;
            }
        }

        if(!valid) { //Ask to make a new project at directory
            std::cout << "No project at path, making a new one\n";
            std::cout << "New project name? ";
            std::string newName;
            std::cin >> newName;
            CreateProject(newName, projectDir);
            projectDir = projectDir + newName; //Make sure to adjust the project directory
        }

        ProjectSettings *loadedProj = new ProjectSettings();

        std::ifstream fileStream;

        fileStream.open(projectDir + "\\ProjectSettings\\ProjectSettings" + loadedProj->mExtension);

        if (!fileStream.is_open()) {
            std::cout<< "Error Loading Project Settings File\n";
        } else //File exists
        {
            std::cout<< "Found Project Settings File\n";
            fileStream >> loadedProj->mProjectName;
            //Load the resources for the assets folder
            std::string assetDir = projectDir + "\\Assets\\";
            GetMetaDataAtDir(loadedProj, assetDir);



        }
        fileStream.close();

        return loadedProj;
    }

    void Serializer::GetMetaDataAtDir(ProjectSettings *parentSettings, std::string dir) {
        std::string extension = "*.meta"; //Extension for meta data
        std::string name;
        for (auto & p : std::filesystem::recursive_directory_iterator(dir))
        {
            name = p.path().u8string();
            if(name.substr(name.find_last_of(".") + 1) == "meta") {
                std::cout << name << std::endl;
            }

        }

        //WIN32_FIND_DATA search_data;
//
        //memset(&search_data, 0, sizeof(WIN32_FIND_DATA));
//
        //HANDLE handle = FindFirstFile((dir).c_str(), &search_data);
//
        //while(handle != INVALID_HANDLE_VALUE)
        //{
        //    if((search_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) //If the file is a directory
        //    {
        //        // Call our function again to search in this sub-directory
        //        std::cout<<"Found a directory\n";
        //        std::string newDir = (CHAR)"./" + search_data.cFileName;
        //        GetMetaDataAtDir(parentSettings, newDir);
        //    } else {
        //        printf("Found file: %s\r\n", search_data.cFileName);
//
        //        if (FindNextFile(handle, &search_data) == FALSE)
        //            break;
        //    }
        //}
    }

}