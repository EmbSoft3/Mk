/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
*
* This file is part of Mk.
*
* Mk is free software. Redistribution and use in source and binary forms, with or
* without modification, are permitted provided that the following conditions are
* met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*    2. Redistributions in binary form must reproduce the above copyright notice,
*       this list of conditions and the following disclaimer in the documentation
*       and/or other materials provided with the distribution.
*    3. Neither the name of the copyright holder nor the names of its contributors
*       may be used to endorse or promote products derived from this software
*       without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @file mk_display_application_types.h
* @brief Déclaration des types dédiés au module 'Application'.
* @date 5 mai 2019
*
*/

#ifndef MK_DISPLAY_APPLICATION_TYPES_H
#define MK_DISPLAY_APPLICATION_TYPES_H

/**
 * @enum T_mkApplicationType
 * @brief Déclaration de l'énumération T_mkApplicationType.
 *
 */

typedef enum T_mkApplicationType
{
   K_MK_APPLICATION_TYPE_STATIC = 0,                     /*!< Cet identifiant indique que l'application est statique. */
   K_MK_APPLICATION_TYPE_DYNAMIC = 1,                    /*!< Cet identifiant indique que l'application est dynamiquement. */
   K_MK_APPLICATION_TYPE_DAEMON = 2                      /*!< Cet identifiant indique que l'application est une application d'arrière plan. */
} T_mkApplicationType;

/**
 * @enum T_mkApplicationState
 * @brief Déclaration de l'énumération T_mkApplicationState.
 *
 */

typedef enum T_mkApplicationState
{
   K_MK_APPLICATION_STATE_INSTALLED = 0,                 /*!< Cet identifiant indique que l'application est installée. */
   K_MK_APPLICATION_STATE_UNINSTALLED = 1,               /*!< Cet identifiant indique que l'application est en cours de désinstallation. */
   K_MK_APPLICATION_STATE_RUNNING = 2                    /*!< Cet identifiant indique que l'application est en cours d'exécution. */
} T_mkApplicationState;

/**
 * @enum T_mkApplicationRequestType
 * @brief Déclaration de la structure T_mkApplicationRequestType.
 */

typedef enum T_mkApplicationRequestType
{
   K_MK_DISPLAY_REQUEST_APPLICATION_INSTALL = 0x0,       /*!< Définition de l'identifiant de la requête 'Application-Install'. */
   K_MK_DISPLAY_REQUEST_APPLICATION_UNINSTALL = 0x1,     /*!< Définition de l'identifiant de la requête 'Application-Delete'. */
   K_MK_DISPLAY_REQUEST_APPLICATION_LAUNCH = 0x2,        /*!< Définition de l'identifiant de la requête 'Application-Launch'. */
   K_MK_DISPLAY_REQUEST_APPLICATION_CLOSE = 0x3,         /*!< Définition de l'identifiant de la requête 'Application-Close'. */
   K_MK_DISPLAY_REQUEST_APPLICATION_TERMINATE = 0x4,     /*!< Définition de l'identifiant de la requête 'Application-Terminate'. */
   K_MK_DISPLAY_REQUEST_APPLICATION_METADATA = 0x5,      /*!< Définition de l'identifiant de la requête 'Application-Metada'. */
   K_MK_DISPLAY_REQUEST_APPLICATION_ATTRIBUTE = 0x6      /*!< Définition de l'identifiant de la requête 'Application-Attribute'. */
} T_mkApplicationRequestType;

/**
 * @struct T_mkApplicationLayer
 * @brief Déclaration de la structure T_mkApplicationLayer.
 *
 */

typedef struct T_mkApplicationLayer T_mkApplicationLayer;
struct T_mkApplicationLayer
{
   uint16_t type;                                        /*!< Ce membre contient le type du contrôle applicatif (\ref K_MK_CONTROL_APPLICATION). La position de cet attribut ne doit pas être modifiée. */
   uint16_t id;                                          /*!< Ce membre contient l'identifiant unique du contrôle applicatif \ref T_mkApplication. La position de cet attribut ne doit pas être modifiée. */
};

/**
 * @struct T_mkApplicationMetadata
 * @brief Déclaration de la structure T_mkApplicationMetadata.
 *
 */

typedef struct T_mkApplicationMetadata T_mkApplicationMetadata;
struct T_mkApplicationMetadata
{
   T_str8 name;                                          /*!< Ce membre contient l'adresse d'une chaine de caractères UTF8 stockant le nom de l'application (valeur \ref K_MK_NULL si non utilisé). */
   T_str8 author;                                        /*!< Ce membre contient l'adresse d'une chaine de caractères UTF8 stockant le nom de l'auteur de l'application (valeur \ref K_MK_NULL si non utilisé). */
   T_str8 version;                                       /*!< Ce membre contient l'adresse d'une chaine de caractères UTF8 stockant la version de l'application (valeur \ref K_MK_NULL si non utilisé). */
   T_str8 description;                                   /*!< Ce membre contient l'adresse d'une chaine de caractères UTF8 stockant la description de l'application (valeur \ref K_MK_NULL si non utilisé). */
   T_str8 iconPath;                                      /*!< Ce membre contient l'adresse d'une chaine de caractères UTF8 stockant le chemin du logo de l'application (valeur \ref K_MK_NULL si non utilisé). */
   T_mkAddr iconAddr;                                    /*!< Ce membre contient l'adresse de chargement du logo en mémoire. */
};

/**
 * @struct T_mkApplicationDescriptor
 * @brief Déclaration de la structure T_mkApplicationDescriptor.
 *
 */

typedef struct T_mkApplicationDescriptor T_mkApplicationDescriptor;
struct T_mkApplicationDescriptor
{
   uint8_t type;                                         /*!< Ce membre contient le type de l'application (\ref T_mkApplicationType). */
   uint8_t taskType;                                     /*!< Ce membre contient le type de la tâche principale (\ref T_mkTaskType). */
   uint8_t gfxPage;                                      /*!< Ce membre contient la valeur \ref K_MK_TRUE si une page de mémoire graphique doit être allouée, sinon la valeur \ref K_MK_FALSE. */
   uint8_t memPage;                                      /*!< Ce membre contient la valeur \ref K_MK_TRUE si une page de mémoire standard doit être allouée, sinon la valeur \ref K_MK_FALSE. */
   T_mkAddr stackAddr;                                   /*!< Ce membre contient l'adresse de la stack de l'application. */
   uint32_t stackSize;                                   /*!< Ce membre contient la taille de la stack [en octets]. */
   T_mkAddress entryPoint;                               /*!< Ce membre contient l'adresse de la fonction de démarrage de l'application. */
   T_mkAddr arg;                                         /*!< Ce membre contient la valeur de l'argument de l'application. Il est dédié au application statique. */
};

/**
 * @struct T_mkApplicationMemoryPage
 * @brief Déclaration de la structure T_mkApplicationMemoryPage.
 *
 */

typedef struct T_mkApplicationMemoryPage T_mkApplicationMemoryPage;
struct T_mkApplicationMemoryPage
{
   T_mkAddr gfxAddr;                                     /*!< Ce membre contient l'adresse de la page mémoire graphique allouée (ou la valeur \ref K_MK_NULL si aucune page n'a été allouée). */
   T_mkAddr memAddr;                                     /*!< Ce membre contient l'adresse de la page mémoire standard allouée (ou la valeur \ref K_MK_NULL si aucune page n'a été allouée). */
   T_mkAddr deploymentAddr;                              /*!< Ce membre contient l'adresse de la page mémoire où une application dynamique a été déployée (ou la valeur \ref K_MK_NULL si aucune page n'a été allouée). */
};

/**
 * @struct T_mkApplicationTask
 * @brief Déclaration de la structure T_mkApplicationTask.
 *
 */

typedef struct T_mkApplicationTask T_mkApplicationTask;
struct T_mkApplicationTask
{
   T_mkTask* addr;                                       /*!< Ce membre contient l'adresse de la tâche principale de l'application. */
   T_mkStack stack;                                      /*!< Ce membre contient les caractéristiques mémoires de la stack de l'application. */
   uint32_t identifier;                                  /*!< Ce membre contient l'identifiant de la tâche principale de l'application. */
   uint32_t priority;                                    /*!< Ce membre contient la priorité de la tâche principale de l'application. */
   T_mkAddr arg;                                         /*!< Ce membre contient la valeur de l'argument de l'application. */
};

/**
 * @struct T_mkApplicationDynamicAttributes
 * @brief Déclaration de la structure T_mkApplicationDynamicAttributes.
 *
 */

typedef struct T_mkApplicationDynamicAttributes T_mkApplicationDynamicAttributes;
struct T_mkApplicationDynamicAttributes
{
   int8_t fileBuf [ K_MK_FILE_MAX_NAME_LENGTH + 1 ];     /*!< Ce membre contient une chaine de caractères stockant le chemin et le nom du fichier de programmation d'une application dynamique. */
   T_str8 fileName;                                      /*!< Ce membre contient l'adresse de la chaine de caractères stockant le nom du fichier de programmation de l'application. */
   T_str8 filePath;                                      /*!< Ce membre contient l'adresse de la chaine de caractères stockant le chemin du fichier de programmation de l'application. */
   T_mkExternalLibrariesList libraries;                  /*!< Ce membre contient la liste des bibliothèques externes utilisées pour résoudre les symboles de l'application. */
};

/**
 * @struct T_mkApplication
 * @brief Déclaration de la structure T_mkApplication.
 *
 */

typedef struct T_mkApplication T_mkApplication;
struct T_mkApplication
{
   T_mkApplicationLayer layer;                           /*!< Ce membre contient le registre d'identification d'une application de type \ref T_mkApplication. La position de cet attribut ne doit pas être modifiée. */
   T_mkApplicationState state;                           /*!< Ce membre contient l'état de l'application (\ref T_mkApplicationState). */
   T_mkApplicationDescriptor descriptor;                 /*!< Ce membre contient le descripteur de l'application. */
   T_mkApplicationDynamicAttributes dynamic;             /*!< Ce membre contient les attributs dynamiqque d'une application. */
   T_mkDispatcherAttributes attribute;                   /*!< Ce membre contient les attributs générique d'une l'application. */
   T_mkApplicationMemoryPage page;                       /*!< Ce membre contient l'adresse des pages mémoire de l'application. */
   T_mkApplicationMetadata metadata;                     /*!< Ce membre contient les métadonnées de l'application. */
   T_mkApplicationTask task;                             /*!< Ce membre contient les attributs relatifs à la tâche principale de l'application. */
   T_mkApplication* next;                                /*!< Ce membre contient l'adresse de la prochaine application ou la valeur \ref K_MK_NULL. */
   T_mkApplication* previous;                            /*!< Ce membre contient l'adresse de la précédente application ou la valeur \ref K_MK_NULL. */
};

/**
 * @struct T_mkApplicationGarbageItem
 * @brief Déclaration de la structure T_mkApplicationGarbageItem.
 *
 */

typedef struct T_mkApplicationGarbageItem T_mkApplicationGarbageItem;
struct T_mkApplicationGarbageItem
{
   T_mkApplication* application;                         /*!< Ce membre contient l'adresse de l'application à désallouer. */
   uint32_t elapseCounter;                               /*!< Ce membre contient la durée de vie des page mémoire [en frame]. */
   T_mkApplicationGarbageItem* next;                     /*!< Ce membre contient l'adresse du prochain élément ou la valeur \ref K_MK_NULL. */
   T_mkApplicationGarbageItem* previous;                 /*!< Ce membre contient l'adresse du précédent élément ou la valeur \ref K_MK_NULL. */
};


/**
 *
 */

/**
 * @struct T_mkApplicationList
 * @brief Déclaration de la structure T_mkApplicationList.
 *
 */

typedef struct T_mkApplicationList T_mkApplicationList;
struct T_mkApplicationList
{
   T_mkApplication* first;                               /*!< Ce membre contient l'adresse de la première application dans la liste. */
   T_mkApplication* last;                                /*!< Ce membre contient l'adresse de la dernière application dans la liste. */
   T_mkApplicationGarbageItem* deleted;                  /*!< Ce membre contient l'adresse des pages mémoires à désallouée. */
};

/**
 *
 */

/**
 * @struct T_mkApplicationCmdLineArguments
 * @brief Déclaration de la structure T_mkApplicationCmdLineArguments.
 *
 */

typedef struct T_mkApplicationCmdLineArguments T_mkApplicationCmdLineArguments;
struct T_mkApplicationCmdLineArguments
{
   uint32_t chain [ K_MK_DISPLAY_APPLICATION_ARGV_SIZE ];        /*!< Ce membre contient les arguments de l'application exécutée en ligne de commande. */
};

/**
 * @struct T_mkApplicationHeader
 * @brief Déclaration de la structure T_mkApplicationHeader.
 *        Cettre structure définit l'entête d'une application dynamique chargée en mémoire.
 *
 */

typedef struct T_mkApplicationHeader T_mkApplicationHeader;
struct T_mkApplicationHeader
{
   uint32_t magicNumber;                                 /*!< Ce membre contient le magicNumber d'une application dynamique. */
   uint32_t headerSize;                                  /*!< Ce membre contient la taille de l'entête [en octets]. */
   uint32_t reserved;                                    /*!< Reserved. */
   uint32_t version;                                     /*!< Ce membre contient la version de l'entête. */
   T_mkAddr descriptorAddr;                              /*!< Ce membre contient l'adresse du descripteur d'application (\ref T_mkApplicationDescriptor). */
   uint32_t descriptorSize;                              /*!< Ce membre contient la taille du descripteur d'application [en octets]. */
   T_mkAddr metadataAddr;                                /*!< Ce membre contient l'adresse du descriteur de métadonnées de l'application (\ref T_mkApplicationMetadata). */
   uint32_t metadataSize;                                /*!< Ce membre contient la taille du descripteur de métadonnées de l'application [en octets]. */
   T_mkAddr argAddr;                                     /*!< Ce membre contient l'adresse de la table des arguments saisis en ligne de commande (\ref T_mkApplicationCmdLineArguments). */
   uint32_t argSize;                                     /*!< Ce membre contient la taille de la table des arguments [en octets]. */
};

/**
 * @struct T_mkApplicationDynamicHeader
 * @brief Déclaration de la structure T_mkApplicationDynamicHeader.
 *
 */

typedef struct T_mkApplicationDynamicHeader T_mkApplicationDynamicHeader;
struct T_mkApplicationDynamicHeader
{
   T_mkApplicationHeader header;                         /*!< Ce membre contient l'entête de l'application. */
   T_mkApplicationDescriptor descriptor;                 /*!< Ce membre contient le descripteur de l'application. */
   T_mkApplicationMetadata metadata;                     /*!< Ce membre contient le descripteur de métadonnées de l'application. */
   T_mkApplicationCmdLineArguments args;                 /*!< Ce membre contient les arguments de l'application. */
};

/**
 *
 */

/**
 * @struct T_mkApplicationRequestContent
 * @brief Déclaration de la structure T_mkApplicationRequestContent.
 */

typedef struct T_mkApplicationRequestContent T_mkApplicationRequestContent;
struct T_mkApplicationRequestContent
{
   T_mkApplicationDescriptor descriptor;                 /*!< Ce membre contient l'adresse d'un descripteur d'application de type \ref T_mkApplicationDescriptor. */
   T_str8 path;                                          /*!< Ce membre contient l'adresse de la chaine de caractères stockant le chemin du fichier de programmation de l'application. */
   T_mkAddr volume;                                      /*!< Ce membre contient l'adresse du volume stockant le fichier de programmation de l'application. */
   T_mkAddr addr;                                        /*!< Ce membre contient l'adresse des métadonnées ou des attributs de l'application (\ref T_mkApplicationMetadata ou \ref T_mkDispatcherAttributes). */
};

/**
 * @struct T_mkContainerRequest
 * @brief Déclaration de la structure T_mkContainerRequest.
 */

typedef struct T_mkApplicationRequest T_mkApplicationRequest;
struct T_mkApplicationRequest
{
   uint32_t id;                                          /*!< Ce membre contient l'identifiant de la requête (\ref T_mkApplicationRequestType). */
   T_mkApplication* application;                         /*!< Ce membre contient l'adresse d'une application de type \ref T_mkApplication. */
   T_mkApplicationRequestContent content;                /*!< Ce membre contient les arguments de la requête. */
   T_mkCode* result;                                     /*!< Ce membre contient le code de retour de la requête. */
   T_mkCallback* callback;                               /*!< Ce membre contient l'adresse d'une fonction de rappel de type \ref T_mkCallback. */
};

/**
 *
 */

#endif


