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
* @file mk_display_types.h
* @brief Déclaration des types dédiés au module 'Display'.
* @date 16 mars 2019
*
*/

#ifndef MK_DISPLAY_TYPES_H
#define MK_DISPLAY_TYPES_H

/**
 * @enum T_mkDisplayBytesPerPixel
 * @brief Déclaration de l'énumération T_mkDisplayBytesPerPixel.
 */

typedef enum T_mkDisplayBytesPerPixel
{
   K_MK_DISPLAY_RGB888 = 0x3,                                           /*!< Définition du nombre d'octets codant un pixel au format ARGB888. */
   K_MK_DISPLAY_ARGB8888 = 0x4                                          /*!< Définition du nombre d'octets codant un pixel au format ARGB8888. */
} T_mkDisplayBytesPerPixel;

/**
 * @enum T_mkDisplayEngineRequestType
 * @brief Déclaration de l'énumération T_mkDisplayEngineRequestType.
 */

typedef enum T_mkDisplayEngineRequestType
{
   K_MK_DISPLAY_REQUEST_TYPE_ENABLE_BACKGROUND = 0x0,                   /*!< Définition de l'identifiant d'une requête de type 'EnableBackground'. */
   K_MK_DISPLAY_REQUEST_TYPE_DISABLE_BACKGROUND = 0x1,                  /*!< Définition de l'identifiant d'une requête de type 'DisableBackground'. */
   K_MK_DISPLAY_REQUEST_TYPE_ENABLE_FOREGROUND = 0x2,                   /*!< Définition de l'identifiant d'une requête de type 'EnableForeground'. */
   K_MK_DISPLAY_REQUEST_TYPE_DISABLE_FOREGROUND = 0x3,                  /*!< Définition de l'identifiant d'une requête de type 'DisableForeground'. */
   K_MK_DISPLAY_REQUEST_TYPE_NEXT_FRAME = 0x4                           /*!< Définition de l'identifiant d'une requête de type 'NextFrame'. */
} T_mkDisplayEngineRequestType;

/**
 * @struct T_mkDisplayEngineRequest
 * @brief Déclaration de la structure T_mkDisplayEngineRequest.
 */

typedef struct T_mkDisplayEngineRequest T_mkDisplayEngineRequest;
struct T_mkDisplayEngineRequest
{
   T_mkDisplayEngineRequestType id;                                     /*!< Ce membre contient l'identifiant d'une requête de type 'Engine'. */
};

/**
 * @struct T_mkDisplayHandler
 * @brief Déclaration de la structure T_mkDisplayHandler.
 */

typedef struct T_mkDisplayHandler T_mkDisplayHandler;
struct T_mkDisplayHandler
{
   T_mkTask* task;                                                      /*!< Ce membre contient la tâche du gestionnaire de requêtes. */
   T_mkStack stack;                                                     /*!< Ce membre contient les caractéristiques mémoire du gestionnaire de requêtes. */
   uint32_t buf [ K_MK_DISPLAY_TASK_HANDLER_STACK_SIZE ];               /*!< Ce membre contient la stack du gestionnaire de requêtes. */
   T_mkMail* mail;                                                      /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination du moteur graphique. */
   T_mkPoolArea area;                                                   /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   T_mkPool* containerPool;                                             /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkContainer. */
   T_mkPoolArea containerArea;                                          /*!< Ce membre contient la mémoire dédiée aux containers. */
   T_mkPool* applicationPool;                                           /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkApplication. */
   T_mkPoolArea applicationArea;                                        /*!< Ce membre contient la mémoire dédiée aux applications. */
   T_mkEvent* event;                                                    /*!< Ce membre contient le registre d'événements du gestionnaire de requêtes. */
};

/**
 * @struct T_mkDisplayPainter
 * @brief Déclaration de la structure T_mkDisplayPainter.
 * @note La stack non privilégiée (buf) n'est pas allouée dans cette structure délibérement (structure privilégiée).
 */

typedef struct T_mkDisplayPainter T_mkDisplayPainter;
struct T_mkDisplayPainter
{
   T_mkTask* privilegedTask;                                            /*!< Ce membre contient la tâche de peinture privilégiée. */
   T_mkTask* unprivilegedTask;                                          /*!< Ce membre contient la tâche de peinture non privilégiée. */
   T_mkStack privilegedStack;                                           /*!< Ce membre contient les caractéristiques mémoire de la stack de peinture privilégiée. */
   T_mkStack unprivilegedStack;                                         /*!< Ce membre contient les caractéristiques mémoire de la stack de peinture non privilégiée. */
   T_mkEvent* frameEvent;                                               /*!< Ce membre contient le registre d'événements synchronisant la tâche de peinture avec les interruptions LTDC. */
   T_mkEvent* taskEvent;                                                /*!< Ce membre contient le registre d'événements synchronisant les tâches de peinture privilégiée et non privilégiée. */
   T_mkSemaphore* semaphore;                                            /*!< Ce membre contient le sémaphore synchronisant la tâche de peinture privilégiée avec les applications (lors de la mise à jour des containers). */
   T_mkSemaphore* unprivilegedSemaphore;                                /*!< Ce membre contient le sémaphore synchronisant la tâche de peinture non privilégiée avec les applications (lors de la mise à jour des containers). */
   uint32_t buf [ K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_STACK_SIZE ];    /*!< Ce membre contient la stack de peinture privilégiée. */
};

/**
 * @struct T_mkDisplayListener
 * @brief Déclaration de la structure T_mkDisplayListener.
 * @note La stack non privilégiée (buf) n'est pas allouée dans cette structure délibérement (structure privilégiée).
 */

typedef struct T_mkDisplayListener T_mkDisplayListener;
struct T_mkDisplayListener
{
   T_mkTask* privilegedTask;                                            /*!< Ce membre contient la tâche d'écoute privilégiée. */
   T_mkTask* unprivilegedTask;                                          /*!< Ce membre contient la tâche d'écoute non privilégiée. */
   T_mkStack privilegedStack;                                           /*!< Ce membre contient les caractéristiques mémoire de la stack d'écoute privilégiée. */
   T_mkStack unprivilegedStack;                                         /*!< Ce membre contient les caractéristiques mémoire de la stack d'écoute non privilégiée. */
   T_mkEvent* taskEvent;                                                /*!< Ce membre contient le registre d'événements synchronisant les tâches d'écoute privilégiée et non privilégiée. */
   T_mkSemaphore* semaphore;                                            /*!< Ce membre contient le sémaphore synchronisant la tâche d'écoute privilégiée avec les applications (lors de la mise à jour des containers). */
   T_mkSemaphore* unprivilegedSemaphore;                                /*!< Ce membre contient le sémaphore synchronisant la tâche d'écoute non privilégiée avec les applications (lors de la mise à jour des containers). */
   uint32_t buf [ K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_STACK_SIZE ];   /*!< Ce membre contient la stack d'écoute privilégiée. */
};

/**
 * @struct T_mkDisplayApplication
 * @brief Déclaration de la structure T_mkDisplayApplication.
 */

typedef struct T_mkDisplayApplication T_mkDisplayApplication;
struct T_mkDisplayApplication
{
   T_mkPool* pool;                                                      /*!< Ce membre contient le gestionnaire mémoire utilisé pour déployer les applications externes en mémoire. */
   T_mkPoolArea area;                                                   /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique des applications externes. */
   T_mkPool* deletedPool;                                               /*!< Ce membre contient le gestionnaire mémoire utilisé pour désallouer les applications. */
   T_mkPoolArea deletedArea;                                            /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique servant à la désallocation des applications. */
   T_mkApplication* current;                                            /*!< Ce membre contient l'adresse de l'application affichée. */
   T_mkApplication* main;                                               /*!< Ce membre contient l'adresse de l'application principale. C'est la première application lancée au démarrage du système. */
   T_mkApplicationList list;                                            /*!< Ce membre contient la liste des applications. */
   uint32_t numberOfInstalledApps;                                      /*!< Ce membre contient le nombre d'applications installées. */
   uint32_t numberOfRunningApps;                                        /*!< Ce membre contient le nombre d'applications en cours de fonctionnement. */
};

/**
 * @struct T_mkDisplayStatus
 * @brief Déclaration de la structure T_mkDisplayStatus.
 */

typedef volatile struct T_mkDisplayStatus T_mkDisplayStatus;
struct T_mkDisplayStatus
{
   unsigned_t wakeup:1;                                                 /*!< Ce bit indique au moteur de réveiller (1) la tâche de peinture non (0). */
   unsigned_t criticalLock:1;                                           /*!< Ce bit indique au moteur d'exécuter uniquement les fonctions d'écoutes présentes dans le container critique (1) ou non (0). */
   unsigned_t listenerLock:1;                                           /*!< Ce bit indique que la boucle des listeners non privilégiés a été bloquée pendant plus de \ref K_MK_DISPLAY_TASK_UNPRIVILEGED_TASK_TIMEOUT millisecondes (1) ou non (0). */
   unsigned_t painterLock:1;                                            /*!< Ce bit indique que la boucle des painters non privilégiés a été bloquée pendant plus de \ref K_MK_DISPLAY_TASK_UNPRIVILEGED_TASK_TIMEOUT millisecondes (1) ou non (0). */
   unsigned_t reserved:28;                                              /*!< Ces bits sont réservés pour un usage ultérieur. */
};

/**
 * @struct T_mkDisplayFrameBufferStatus
 * @brief Déclaration de la structure T_mkDisplayFrameBufferStatus.
 */

typedef volatile struct T_mkDisplayFrameBufferStatus T_mkDisplayFrameBufferStatus;
struct T_mkDisplayFrameBufferStatus
{
   unsigned_t backgroundLayer:1;                                        /*!< Ce bit indique que le layer d'arrière plan doit être activé (1) à la fin de la trame courante. */
   unsigned_t foregroundLayer:1;                                        /*!< Ce bit indique que le layer de premier plan doit être activé (1) à la fin de la trame courante. */
   unsigned_t reserved:30;                                              /*!< Ces bits sont réservés pour un usage ultérieur. */
};

/**
 * @struct T_mkDisplayScreen
 * @brief Déclaration de la structure T_mkDisplayScreen.
 */

typedef struct T_mkDisplayScreen T_mkDisplayScreen;
struct T_mkDisplayScreen
{
   uint32_t width;                                                      /*!< Ce membre contient la largeur de l'écran [en pixel]. */
   uint32_t height;                                                     /*!< Ce membre contient la hauteur de l'écran [en pixel]. */
   uint32_t resolutionX;                                                /*!< Ce membre contient la résolution de l'écran sur l'axe X [en pixel/m]. */
   uint32_t resolutionY;                                                /*!< Ce membre contient la résolution de l'écran sur l'axe Y [en pixel/m]. */
   uint32_t bytesPerPixel [ 2 ];                                        /*!< Ce membre contient la résolution (\ref K_MK_DISPLAY_RGB888 ou \ref K_MK_DISPLAY_ARGB8888) des pixels du premier plan (\ref K_MK_GRAPHICS_FOREGROUND) et de l'arrière plan (\ref K_MK_GRAPHICS_BACKGROUND). */
};

/**
 * @struct T_mkDisplayFrameBuffer
 * @brief Déclaration de la structure T_mkDisplayFrameBuffer.
 */

typedef struct T_mkDisplayFrameBuffer T_mkDisplayFrameBuffer;
struct T_mkDisplayFrameBuffer
{
   uint32_t* addr [ 2 ];                                                /*!< Ce membre contient l'adresse des buffers graphiques des layers de premier-plan (\ref K_MK_GRAPHICS_FOREGROUND) et d'arrière plan (\ref K_MK_GRAPHICS_BACKGROUND). */
   vuint32_t validity;                                                  /*!< Ce membre contient la valeur (1) lorsque le couple de buffers graphiques est prêt à être affiché, sinon (0). */
   T_mkDisplayFrameBufferStatus status;                                 /*!< Ce membre contient le registre de statut des buffers graphiques. */
   T_mkDisplayFrameBuffer* next;                                        /*!< Ce membre contient l'adresse de la prochaine structure graphique de la liste. */
};

/**
 * @struct T_mkDisplayFramePointer
 * @brief Déclaration de la structure T_mkDisplayFramePointer.
 *
 * @note Le moteur graphique est constitué de \ref K_MK_DISPLAY_FRAME_BUFFER_NUMBER buffers graphiques (\ref T_mkDisplayFrameBuffer).
 *       La mise à jour des buffers graphiques est réalisée par le biais de la tâche de gestion des requêtes et par les tâches de peintures.
 *       Les tâches de peinture transmettent une ou plusieurs requêtes à la tâche de gestion des requêtes. Lorsque toutes les requêtes de dessin ont été envoyées, le message \ref K_MK_DISPLAY_REQUEST_TYPE_NEXT_FRAME
 *       est envoyé à la tâche de gestion pour passer au prochain buffer graphique. Du point de vue des tâches de peinture, les requêtes sont exécutées de manière asynchrone.
 *       On déclare donc 3 pointeurs de buffers graphique :
 *
 *       \li currentBufferPrinted : ce pointeur contient l'adresse du buffer affiché sur l'écran. Il est réservé au périphérique LTDC.
 *       \li currentBufferUpdated : ce pointeur contient l'adresse du buffer utilisé par la tâche de gestion des requêtes. Il est dédié à l'accélérateur graphique chromart. Ce buffer sera le prochain buffer à être affiché à l'écran.
 *       \li currentBufferUsed    : ce pointeur contient l'adresse du buffer utilisé par l'utilisateur. Il contient l'adresse du buffer utilisé par les tâches de peinture. Lorsque l'exécution des fonctions de peinture est plus rapide que
 *                                  le traitement des requêtes, le remplissage des buffers successifs est déclenché. Les buffers doivent donc être adressé par cette variable.
 *
 */

typedef struct T_mkDisplayFramePointer T_mkDisplayFramePointer;
struct T_mkDisplayFramePointer
{
   T_mkDisplayFrameBuffer* volatile currentBufferPrinted;               /*!< Ce membre contient l'adresse du buffer affiché sur l'écran (réservé au matériel). */
   T_mkDisplayFrameBuffer* volatile currentBufferUsed;                  /*!< Ce membre contient l'adresse du buffer utilisé par l'utilisateur (réservé aux tâches de peintures). */
   T_mkDisplayFrameBuffer* volatile currentBufferUpdated;               /*!< Ce membre contient l'adresse du buffer utilisé par l'accélérateur chromart (réservé à la tâche de gestion des requêtes). */
};

/**
 * @struct T_mkDisplayFramerate
 * @brief Déclaration de la structure T_mkDisplayFrame.
 */

typedef struct T_mkDisplayFrameRate T_mkDisplayFrameRate;
struct T_mkDisplayFrameRate
{
   vuint32_t counter;                                                   /*!< Ce membre stocke le nombre de frames écrites durant la période de calcul du framerate. */
   vuint32_t period;                                                    /*!< Ce membre stocke la période de calcul du framerate. */
   vuint32_t value;                                                     /*!< Ce membre stocke la valeur du framerate courant. */
};

/**
 * @struct T_mkDisplayFont
 * @brief Déclaration de la structure T_mkDisplayFont.
 */

typedef struct T_mkDisplayFont T_mkDisplayFont;
struct T_mkDisplayFont
{
   T_mkFont handle;                                                     /*!< Ce membre contient la police de caractère utilisée par défaut par le moteur graphique. */
   T_mkFontPage page [ K_MK_FONT_DEFAULT_NUMBER_OF_PAGES ];             /*!< Ce membre contient les descripteurs de pages de la police de caractères par défaut. */
};

/**
 * @struct T_mkDisplay
 * @brief Déclaration de la structure T_mkDisplay.
 */

typedef struct T_mkDisplay T_mkDisplay;
struct T_mkDisplay
{
   T_mkDisplayStatus status;                                            /*!< Ce membre contient le registre de statut du moteur graphique. */
   T_mkDisplayScreen screen;                                            /*!< Ce membre contient les dimensions de l'écran. */
   T_mkDisplayHandler handler;                                          /*!< Ce membre contient les données de la tâche de gestion des requêtes. */
   T_mkDisplayPainter painter;                                          /*!< Ce membre contient les données des tâches de peinture. */
   T_mkDisplayListener listener;                                        /*!< Ce membre contient les données des tâches d'écoute'. */
   T_mkListenerMessage listenerMessage;                                 /*!< Ce membre contient les messages à destination des tâches d'écoute. */
   T_mkDisplayFramePointer pnt;                                         /*!< Ce membre contient les adresses des buffers affichés, utilisés et en cours d'actualisation. */
   T_mkDisplayFrameRate framerate;                                      /*!< Ce membre contient les données permettant de calculer le framerate. */
   T_mkDisplayFrameBuffer frame [K_MK_DISPLAY_FRAME_BUFFER_NUMBER];     /*!< Ce membre contient les buffers graphiques. */
   T_mkDisplayFont defaultFont;                                         /*!< Ce membre contient les caractéristiques de la police de caractères par défaut. */
   T_mkDisplayFont defaultFixedFont;                                    /*!< Ce membre contient les caractéristiques de la police de caractères de taille fixe par défaut. */
   T_mkDisplayApplication application;                                  /*!< Ce membre contient la liste des applications. */
   T_mkFactory privilegedFactory;                                       /*!< Ce membre contient la liste des containers privilégiés. */
   T_mkFactory unprivilegedFactory;                                     /*!< Ce membre contient la liste des containers non privilégiés. */
   T_mkContainer* criticalContainer;                                    /*!< Ce membre contient le container utilisé par le système pour afficher les objets critiques. */
   T_mkContainer* frontendContainer;                                    /*!< Ce membre contient le container utilisé par le système pour afficher les objets de premier plan (curseur souris ou autres). */
};

/**
 *
 */

#endif

