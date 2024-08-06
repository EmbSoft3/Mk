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
* @file mk_display_application.h
* @brief Déclaration des fonctions dédiées au module 'Application'.
* @date 6 mai 2019
*
*/

#ifndef MK_DISPLAY_APPLICATION_H
#define MK_DISPLAY_APPLICATION_H

/**
 * @fn T_mkApplication* mk_application_getFirst ( void );
 * @brief Cette fonction retourne l'adresse de la première application présente dans la liste des applications.
 * @return Cette fonction retourne l'adresse de la première application.
 *
 */

T_mkApplication* mk_application_getFirst ( void );

/**
 * @fn T_mkApplication* mk_application_getCurrent ( void );
 * @brief Cette fonction retourne l'adresse de l'application courante.
 * @return Cette fonction retourne l'adresse de l'application courante.
 *
 * @note L'application courante est l'application de premier plan actuellement affichée.
 *
 */

T_mkApplication* mk_application_getCurrent ( void );

/**
 * @fn T_mkApplication* mk_application_getMain ( void );
 * @brief Cette fonction retourne l'adresse de l'application principale.
 * @return Cette fonction retourne l'adresse de l'application principale.
 *
 * @note L'application principale est la première application exécutée par le système au démarrage.
 *
 */

T_mkApplication* mk_application_getMain ( void );

/**
 * @fn T_mkApplication* mk_application_getById ( uint32_t p_id );
 * @brief Cette fonction retourne l'adresse de l'application identifiée par p_id.
 * @return Cette fonction retourne l'adresse d'une application ou la valeur \ref K_MK_NULL si l'application n'a pas été trouvée.
 *
 */

T_mkApplication* mk_application_getById ( uint32_t p_id );

/**
 * @fn uint32_t mk_application_getNumberOfInstalledApps (void );
 * @brief Cette fonction retourne le nombre d'applications installées.
 * @return Cette fonction retourne le nombre d'applications installées.
 *
 */

uint32_t mk_application_getNumberOfInstalledApps (void );

/**
 * @fn uint32_t mk_application_getNumberOfRunningApps ( void );
 * @brief Cette fonction retourne le nombre d'applications en cours d'exécution.
 * @return Cette fonction retourne le nombre d'applications en cours d'exécution.
 *
 */

uint32_t mk_application_getNumberOfRunningApps ( void );

/**
 * @fn T_mkAddr mk_application_getArg ( T_mkApplication* p_application );
 * @brief Cette fonction retourne l'argument d'une application. Pour les applications dynamique, la valeur de l'argument contient l'adresse de l'application.
 *        Pour les applications statique, la valeur de l'argument est définie par l'utilisateur.
 * @param[in] p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 *
 * @return Cette fonction retourne l'argument d'une application.
 *
 */

T_mkAddr mk_application_getArg ( T_mkApplication* p_application );

/**
 * @fn T_mkCode mk_application_getCmdLine ( T_mkApplication* p_application, T_str8* p_chain );
 * @brief Cette fonction retourne l'adresse de la chaine de caractères contenant les arguments d'une application dynamique (saisie en ligne de commande).
 *        L'adresse \ref K_MK_NULL est renvoyée si l'application p_application est de type statique.
 *
 * @param[in]  p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 * @param[out] p_chain       Ce paramètre contient l'adresse d'un pointeur de chaine.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK          : la fonction s'est exécutée correctement.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échouée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_application_getCmdLine ( T_mkApplication* p_application, T_str8* p_chain );

/**
 * @fn T_mkCode mk_application_getArgv ( T_str8 p_chain, T_str8* p_nextChain, T_str8 p_arg, uint32_t p_argLength, T_mkFontUnicode p_fontEncoding );
 * @brief Cette fonction retourne l'adresse du premier argument d'une ligne de commande.
 *
 * @param[in]  p_chain        Ce paramètre contient l'adresse d'un argument de la ligne de commande.
 * @param[out] p_nextChain    Ce paramètre contient l'adresse du prochain argument de la ligne de commande.
 * @param[out] p_arg          Ce paramètre contient la valeur de l'argument récupéré.
 * @param[in]  p_argLength    Ce paramètre contient la taille du buffer où l'argument doit être stocké [en octets].
 * @param[in]  p_fontEncoding Ce paramètre contient l'encodage de la ligne de commande (\ref T_mkFontUnicode).
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK                  : la fonction s'est exécutée correctement.
 *         \li \ref K_MK_ERROR_PARAM         : la fonction a échouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la fonction a échouée car aucun argument n'est disponible.
 *
 */

T_mkCode mk_application_getArgv ( T_str8 p_chain, T_str8* p_nextChain, T_str8 p_arg, uint32_t p_argLength, T_mkFontUnicode p_fontEncoding );

/**
 * @fn T_mkCode mk_application_install ( T_mkApplication** p_application, T_mkApplicationDescriptor* p_descriptor, T_mkApplicationMetadata* p_metadata, T_mkCallback* p_callback );
 * @brief Cette fonction installe une application statique. Un événement \ref K_MK_EVENT_INSTALL est envoyé au dispatcher si l'installation a réussi.
 *
 * @param[out] p_application Ce paramètre contient l'adresse d'un pointeur d'application.
 * @param[in]  p_descriptor  Ce paramètre contient l'adresse d'un descripteur d'application de type \ref T_mkApplicationDescriptor.
 * @param[in]  p_metadata    Ce paramètre contient l'adresse d'un descripteur de métadonnées de type \ref T_mkApplicationMetadata.
 * @param[in]  p_callback    Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : l'installation de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'installation de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : l'installation de l'application a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : l'installation de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : l'installation de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'installation de l'application a échoué car un timeout s'est produit.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_application_callback ( T_mkCode p_result, T_mkApplication* p_application );
 *
 */

T_mkCode mk_application_install ( T_mkApplication** p_application, T_mkApplicationDescriptor* p_descriptor, T_mkApplicationMetadata* p_metadata, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_application_installDynamic ( T_mkApplication** p_application, T_str8 p_filePath, T_str8 p_cmdLineParam, T_mkVolume* p_volume, T_mkCallback* p_callback );
 * @brief Cette fonction installe une application dynamique. Un événement \ref K_MK_EVENT_INSTALL est envoyé au dispatcher si l'installation a réussi.
 *
 * @param[out] p_application  Ce paramètre contient l'adresse d'un pointeur d'application.
 * @param[in]  p_filePath     Ce paramètre contient le chemin et le nom du fichier de programmation (.elf).
 *                            La chaine de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 *                            \n Lorsque le paramètre p_volume est non nul, l'accès est réalisé sur la partition définie par p_volume.
 *                            \n Lorsque le paramètre p_volume est nul, la partition à accéder doit être spécifiée dans la chaine de caractères (cf. fonction \ref mk_file_open).
 * @param[in]  p_cmdLineParam Ce paramètre contient les arguments de l'application.
 * @param[in]  p_volume       Ce paramètre contient l'adresse de la partition où est stocké le fichier de programmation.
 * @param[in]  p_callback     Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK               : l'installation de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM      : l'installation de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC     : l'installation de l'application a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR        : l'installation de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : l'installation de l'application a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : l'installation de l'application a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : l'installation de l'application a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED : l'installation de l'application a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT      : l'installation de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_application_callback ( T_mkCode p_result, T_mkApplication* p_application );
 *
 * @note l_result = mk_application_installDynamic ( &l_application, ( T_str8 ) "mk/apps/pong/pongGameRelease_V10.elf", K_MK_NULL, l_volume, K_MK_NULL ); \n
 *       l_result = mk_application_installDynamic ( &l_application, ( T_str8 ) "mk/apps/blinkLed/blinkLedRelease_V10.elf", ( T_str8 ) "500", l_volume, K_MK_NULL );
 *
 */

T_mkCode mk_application_installDynamic ( T_mkApplication** p_application, T_str8 p_filePath, T_str8 p_cmdLineParam, T_mkVolume* p_volume, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_application_uninstall ( T_mkApplication* p_application, T_mkCallback* p_callback );
 * @brief Cette fonction désinstalle une application. Un événément \ref K_MK_EVENT_UNINSTALL est envoyé au dispatcher si la désinstallation a réussi.
 *
 * @param[in] p_application Ce paramètre contient l'adresse d'une application.
 * @param[in] p_callback    Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : la désinstallation de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la désinstallation de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la désinstallation de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la désinstallation de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : la désinstallation de l'application a échoué car un timeout s'est produit.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_application_callback ( T_mkCode p_result, T_mkApplication* p_application );
 *       Le paramètre p_application prend la valeur \ref K_MK_NULL si la désinstallation a réussi.
 *
 */

T_mkCode mk_application_uninstall ( T_mkApplication* p_application, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_application_terminate ( T_mkApplication* p_application, T_mkCallback* p_callback );
 * @brief Cette fonction détruit la tâche d'une application.
 *
 * @param[in] p_application Ce paramètre contient l'adresse d'une application.
 * @param[in] p_callback    Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : la destruction de la tâche de l'application de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la destruction de la tâche de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la destruction de la tâche de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la destruction de la tâche de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : la destruction de la tâche de l'application a échoué car un timeout s'est produit.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_application_callback ( T_mkCode p_result, T_mkApplication* p_application );
 *
 */

T_mkCode mk_application_terminate ( T_mkApplication* p_application, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_application_uninstall ( T_mkApplication* p_application, T_mkCallback* p_callback );
 * @brief Cette fonction ferme une application. Un événément \ref K_MK_EVENT_CLOSE est envoyé au dispatcher si la fermeture de l'application a réussi.
 *
 * @param[in] p_application Ce paramètre contient l'adresse d'une application.
 * @param[in] p_callback    Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : la fermeture de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la fermeture de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la fermeture de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la fermeture de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : la fermeture de l'application a échoué car un timeout s'est produit.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_application_callback ( T_mkCode p_result );
 *
 */

T_mkCode mk_application_close ( T_mkApplication* p_application, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_application_launch ( T_mkApplication* p_application, uint32_t* p_stackAddr, uint32_t p_stackSize, T_mkPool* p_pool );
 * @brief Cette fonction démarre une application. Un événement \ref K_MK_EVENT_LAUNCH est envoyé au dispatcher si le démarrage de l'application a réussi.
 *
 * @param[in] p_application Ce paramètre contient l'adresse d'une application.
 * @param[in] p_callback    Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le démarrage de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la démarrage de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la démarrage de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la démarrage de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : la démarrage de l'application a échoué car un timeout s'est produit.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_application_callback ( T_mkCode p_result );
 *
 */

T_mkCode mk_application_launch ( T_mkApplication* p_application, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_application_setMetadata ( T_mkApplication* p_application, T_mkApplicationMetadata* p_metadata, T_mkAddr p_address, T_mkCallback* p_callback );
 * @brief Cette fonction configure les métadonnées d'une application. Un événement \ref K_MK_EVENT_METADATA est envoyé au dispatcher si la configuration des métadonnées a réussi.
 *
 * @param[in] p_application Ce paramètre contient l'adresse d'une application.
 * @param[in] p_metadata    Ce paramètre contient l'adresse d'une structure stockant les métadonnées de l'application.
 *                          Il est transmis par référence au moteur. Il ne doit pas être alloué dans un contexte local.
 * @param[in] p_callback    Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : la configuration des métadonnées de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la configuration des métadonnées de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la configuration des métadonnées de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la configuration des métadonnées de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : la configuration des métadonnées de l'application a échoué car un timeout s'est produit.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_application_callback ( T_mkCode p_result );
 *
 */

T_mkCode mk_application_setMetadata ( T_mkApplication* p_application, T_mkApplicationMetadata* p_metadata, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_application_setMetadata ( T_mkApplication* p_application, T_mkApplicationMetadata* p_metadata, T_mkAddr p_address, T_mkCallback* p_callback );
 * @brief Cette fonction configure les attributs (vitesse curseur souris, ...) d'une application.
 *
 * @param[in] p_application Ce paramètre contient l'adresse d'une application.
 * @param[in] p_attributes  Ce paramètre contient l'adresse d'une structure stockant les attributs de l'application.
 *                          Il est transmis par référence au moteur. Il ne doit pas être alloué dans un contexte local.
 * @param[in] p_callback    Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : la configuration des attributs de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la configuration des attributs de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la configuration des attributs de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la configuration des attributs de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : la configuration des attributs de l'application a échoué car un timeout s'est produit.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_application_callback ( T_mkCode p_result );
 *
 */

T_mkCode mk_application_setAttributes ( T_mkApplication* p_application, T_mkDispatcherAttributes* p_attributes, T_mkCallback* p_callback );

/**
 *
 */

#endif

