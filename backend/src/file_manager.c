#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_manager.h"

User *loadUsersFromFile(const char *filename)
{

    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("打开用户文件失败");
        return NULL;
    }

    User *head = NULL, *tail = NULL;
    char line[1024];
    while (fgets(line, sizeof(line), fp))
    {
        if (line[0] == '\n')
            continue;

        User *newUser = malloc(sizeof(User));
        if (!newUser)
        {
            perror("内存分配失败");
            fclose(fp);
            return head;
        }

        sscanf(line, "%[^,],%[^,],%s", newUser->username, newUser->password_hash, newUser->role);
        newUser->next = NULL;

        if (head)
        {
            tail->next = newUser;
            tail = newUser;
        }
        else
        {
            head = newUser;
            tail = newUser;
        }
    }

    fclose(fp);
    return head;
}

int saveUsersToFile(const char *filename, User *head)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        perror("写入文件失败");
        return -1;
    }

    User *current = head;
    while (current)
    {
        fprintf(fp, "%s,%s,%s\n", current->username, current->password_hash, current->role);
        current = current->next;
    }

    fclose(fp);
    return 0;
}

Client *loadClientsFromFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("无法打开文件");
        return NULL;
    }
    Client *head = NULL, *tail = NULL;
    char line[1024];
    while (fgets(line, sizeof(line), fp))
    {
        if (line[0] == '\n')
            continue;

        Client *newClient = malloc(sizeof(Client));
        if (!newClient)
        {
            perror("内存分配失败");
            fclose(fp);
            return head;
        }
        char *phone_token = NULL;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,],%[^,]",
               &newClient->id, newClient->name, newClient->region,
               newClient->address, newClient->legal_person, &newClient->size,
               &newClient->contact_level, newClient->email, line);

        newClient->phone_count = 0;
        phone_token = strtok(line, ";");
        while (phone_token && newClient->phone_count < 100)
        {
            strncpy(newClient->phones[newClient->phone_count], phone_token, sizeof(newClient->phones[0]) - 1);
            newClient->phones[newClient->phone_count][sizeof(newClient->phones[0]) - 1] = '\0';
            newClient->phone_count++;
            phone_token = strtok(NULL, ";");
        }

        newClient->next = NULL;
        if (!head)
        {
            head = tail = newClient;
        }
        else
        {
            tail->next = newClient;
            tail = newClient;
        }
    }

    fclose(fp);
    return head;
}

int saveClientsToFile(const char *filename, Client *head)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        perror("写入文件失败");
        return -1;
    }

    Client *current = head;
    while (current)
    {
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%d,%s,",
                current->id, current->name, current->region, current->address,
                current->legal_person, current->size, current->contact_level,
                current->email);
        for (int i = 0; i < current->phone_count; i++)
        {
            fprintf(fp, "%s", current->phones[i]);
            if (i < current->phone_count - 1)
                fprintf(fp, ";");
        }
        fprintf(fp, "\n");
        current = current->next;
    }

    fclose(fp);
    return 0;
}

// -----  联络员数据文件操作 -----
Contact *loadContactsFromFile(const char *filename)
{
    // printf("file_manager: loadContactsFromFile - 功能待实现\n");
    return NULL;
}

int saveContactsToFile(const char *filename, Contact *head)
{
    // printf("file_manager: saveContactsToFile - 功能待实现\n");
    return 0;
}

// -----  业务员数据文件操作 -----
Sales *loadSalesFromFile(const char *filename)
{
    // printf("file_manager: loadEmployeesFromFile - 功能待实现\n");
    return NULL;
}

int saveSalesToFile(const char *filename, Sales *head)
{
    // printf("file_manager: saveEmployeesToFile - 功能待实现\n");
    return 0;
}

// -----  通信记录数据文件操作 -----
CommunicationRecord *loadCommunicationsFromFile(const char *filename)
{
    // printf("file_manager: loadCommunicationsFromFile - 功能待实现\n");
    return NULL;
}

int saveCommunicationsToFile(const char *filename, CommunicationRecord *head)
{
    // printf("file_manager: saveCommunicationsToFile - 功能待实现\n");
    return 0;
}

// -----  客户分组数据文件操作 -----
Group *loadGroupsFromFile(const char *filename)
{
    // printf("file_manager: loadGroupsFromFile - 功能待实现\n");
    return NULL;
}

int saveGroupsToFile(const char *filename, Group *head)
{
    // printf("file_manager: saveGroupsToFile - 功能待实现\n");
    return 0;
}