/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_utils_strglob.c
* @brief Définition de la fonction mk_utils_strglob.
* @date 12 janv. 2024
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_handleBracketComparaison ( uint32_t p_mode, int8_t p_char, int8_t p_pattern )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Comparaison du caractère avec '-' selon le mode utilisé */
   if ( ( ( p_mode == 0 ) && ( p_char != p_pattern ) ) || ( ( p_mode == 1 ) && ( p_char != p_pattern ) ) )
   {
      /* Le résultat du mode 1 doit être complémenté dans la fonction d'appel. */
      /* Actualisation de la variable de retour */
      l_result = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_handleBracket ( T_str8 p_str, T_str8 p_pattern, uint32_t* p_currentPatternIndex )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Déclaration des variables de travail */
   /* [charlist]  : un seul caractère dans la liste. */
   /* [!charlist] : un seul caractère qui n'est pas dans la liste. */
   uint32_t l_mode = 0; /* 0 = égalité, 1 = différence */
   int8_t l_char;

   /* Récupération du mode de comparaison */
   if ( p_pattern [ *p_currentPatternIndex ] == '!' )
   {
      /* Actualisation du mode */
      l_mode = 1;

      /* On passe au prochain caractère du pattern et de la chaine */
      *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Le caractère '-' peut être présent au début et à la fin de la chaine. */
   if ( ( p_pattern [ *p_currentPatternIndex ] == '-' ) )
   {
      /* Comparaison du caractère avec '-' selon le mode utilisé */
      l_result = mk_utils_handleBracketComparaison ( l_mode, *p_str, '-' );

      /* On passe au prochain caractère du pattern et de la chaine */
      *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Tant que les caractères ']' et '\0' n'ont pas été rencontrés et tant qu'une comparaison n'a pas réussie */
   while ( ( p_pattern [ *p_currentPatternIndex ] != ']' ) && ( p_pattern [ *p_currentPatternIndex ] != '\0' ) && ( l_result == 0 ) )
   {
      /* Le caractère '-' peut être présent au début et à la fin de la chaine. */
      if ( ( p_pattern [ *p_currentPatternIndex ] == '-' ) && ( p_pattern [ ( *p_currentPatternIndex + 1 ) ] == ']' ) )
      {
         /* Comparaison du caractère avec '-' selon le mode utilisé */
         l_result = mk_utils_handleBracketComparaison ( l_mode, *p_str, '-' );
         /* On passe au prochain caractère du pattern et de la chaine */
         *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;
      }

      /* Sinon le caractère '-' indique un plage de valeur */
      else if ( p_pattern [ *p_currentPatternIndex ] == '-' )
      {
         /* Pour chaque valeurs dans la plage (on exclut les 2 bornes) */
         for (   l_char = p_pattern [ ( *p_currentPatternIndex ) - 1 ] + 1 ;
               ( l_char < p_pattern [ ( *p_currentPatternIndex ) + 1 ] ) && ( l_result == 0 ) ;
                 l_char++ )
         {
            /* Réalisation de la comparaison en fonction du mode utilisé */
            l_result = mk_utils_handleBracketComparaison ( l_mode, *p_str, l_char );
         }
         /* On passe au prochain caractère du pattern et de la chaine */
         *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;
      }

      /* Sinon */
      else
      {
         /* Comparaison du caractère avec '-' selon le mode utilisé */
         l_result = mk_utils_handleBracketComparaison ( l_mode, *p_str, p_pattern [ *p_currentPatternIndex ] );
         /* On passe au prochain caractère du pattern et de la chaine */
         *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;
      }
   }

   /* Tant que le pattern n'a pas été entièrement parcouru ou tant que le caractère ']' n'a pas été rencontré */
   while ( ( p_pattern [ *p_currentPatternIndex ] != ']' ) && ( p_pattern [ *p_currentPatternIndex ] != '\0' ) )
   {
      /* On passe au prochain caractère du pattern et de la chaine */
      *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;
   }

   /* Si le mode 1 est actif */
   if ( l_mode == 1 )
   {
      /* On complémente le résultat */
      l_result = ( ~l_result ) & 0x1;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_handleAsteriskComparaison ( T_str8 p_str, T_str8 p_pattern, uint32_t* p_nextPatternIndex )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Si le pattern est égale au caractère '?' */
   if ( p_pattern [ *p_nextPatternIndex ] == '?' )
   {
      /* Ne rien faire */
   }

   /* Sinon si le pattern est égale au caractère '#' */
   else if ( p_pattern [ *p_nextPatternIndex ] == '#' )
   {
      /* Le caractère doit être un digit entre 0 et 9 */
      if ( ( *p_str < '0' ) || ( *p_str > '9' ) )
      {
         /* Actualisation de la variable de retour */
         l_result = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si le pattern est égale au caractère '[' */
   else if ( p_pattern [ *p_nextPatternIndex ] == '[')
   {
      /* Bypass du caractère '[' */
      *p_nextPatternIndex = ( uint32_t ) ( *p_nextPatternIndex ) + 1u;
      /* Traitement de la séquence de caractères */
      l_result = mk_utils_handleBracket ( p_str, p_pattern, p_nextPatternIndex );
   }

   /* Sinon */
   else
   {
      /* Si le caractère est différent du caractère du pattern */
      if ( *p_str != p_pattern [ *p_nextPatternIndex ] )
      {
         /* Actualisation de la variable de retour */
         l_result = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_handleAsterisk ( T_str8 p_str, T_str8 p_pattern, uint32_t* p_currentPatternIndex, uint32_t* p_nextPatternIndex, uint32_t* p_asteriskModeEnabled )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Déclaration de la variable de travail */
   uint32_t l_return = 0;

   /* Réalisation de la comparaison des caractères */
   l_return = mk_utils_handleAsteriskComparaison ( p_str, p_pattern, p_nextPatternIndex );

   /* Si le caractère est différent du caractère du pattern */
   if ( l_return == 0 )
   {
      /* Réinitialisation de la comparaison */
      *p_nextPatternIndex = *p_currentPatternIndex;

      /* Si la chaine de caractères à comparer est terminée */
      if ( ( *( p_str + 1 ) == '\0' ) && ( p_pattern [ *p_nextPatternIndex ] != '\0' ) )
      {
         /* Actualisation de la variable de retour */
         l_result = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Si la comparaison est terminée */
      /* Le prochain caractère pointe sur la fin de chaine ou un caractère spécial */
      if ( ( p_pattern [ *p_nextPatternIndex + 1 ] == '\0' ) || ( p_pattern [ *p_nextPatternIndex + 1 ] == '*' ) )
      {
         /* Désactivation du mode de comparaison */
         *p_asteriskModeEnabled = 0;

         /* Actualisation de l'indice dans le pattern */
         *p_currentPatternIndex = ( uint32_t ) ( *p_nextPatternIndex ) + 1u;
      }

      /* Sinon */
      else
      {
         /* Actualisation de l'indice dans le pattern */
         *p_nextPatternIndex = ( uint32_t ) ( *p_nextPatternIndex ) + 1u;
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_enabledAsteriskMode ( T_str8 p_pattern, uint32_t* p_currentPatternIndex, uint32_t* p_nextPatternIndex )
{
   /* Déclaration de la variable de retour */
   uint32_t l_asteriskModeEnabled = 0;

   /* On regarde si le prochain caractère n'est pas un autre '*' */
   if ( p_pattern [ ( *p_currentPatternIndex ) + 1 ] != '*' )
   {
      /* On active le mode bypass */
      l_asteriskModeEnabled = 1u;

      /* On passe au prochain caractère du pattern */
      /* On conserve la chaine en l'état */
      *p_nextPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* On passe au prochain caractère du pattern */
   *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;

   /* Retour */
   return ( l_asteriskModeEnabled );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_handleHashTag ( T_str8 p_str, uint32_t* p_currentPatternIndex )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Le caractère doit être un digit entre 0 et 9 */
   if ( ( *p_str < '0' ) || ( *p_str > '9' ) )
   {
      /* Actualisation de la variable de retour */
      l_result = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* On passe au prochain caractère du pattern et de la chaine */
   *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_handleDefault ( T_str8 p_str, T_str8 p_pattern, uint32_t* p_currentPatternIndex )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Le caractère doit être un digit entre 0 et 9 */
   if ( *p_str != p_pattern [ *p_currentPatternIndex ] )
   {
      /* Actualisation de la variable de retour */
      l_result = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* On passe au prochain caractère du pattern et de la chaine */
   *p_currentPatternIndex = ( uint32_t ) ( *p_currentPatternIndex ) + 1u;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_handlePattern ( T_str8 p_pattern, uint32_t p_currentPatternIndex, uint32_t p_result )
{
   /* Parcours des derniers caractères du pattern */
   while ( ( p_pattern [ p_currentPatternIndex ] != '\0' ) && ( p_result == 1 ) )
   {
      /* La chaine de caractères utilisateur est terminée */
      /* On actualise la variable de retour si un caractère différent de '*' est présent dans la liste */
      if ( p_pattern [ p_currentPatternIndex ] != '*' )
      {
         /* Actualisation de la variable de retour */
         p_result = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de l'index */
      p_currentPatternIndex = ( uint32_t ) p_currentPatternIndex + 1u;
   }

   /* Retour */
   return ( p_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_strglob ( T_str8 p_str, T_str8 p_pattern )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Déclaration des variables de travail */
   uint32_t l_currentPatternIndex = 0, l_nextPatternIndex = 0, l_asteriskModeEnabled = 0;

   /* Si les paramètres sont valides */
   if ( ( p_str != K_MK_NULL ) && ( p_pattern != K_MK_NULL ) )
   {
      /* '*' : zéro ou plus caractères quelconques. */
      /* '?' : un seul caractère quelconque. */
      /* '#' : un seul digit (0 à 9). */

      /* [charlist]  : un seul caractère dans la liste. */
      /* [!charlist] : un seul caractère qui n'est pas dans la liste. */

      /* Tant que la chaine n'a pas été entièrement parcourue */
      while ( ( ( *p_str ) != '\0' ) && ( l_result == 1u ) )
      {
         /* Si le caractère '*' doit être traité */
         if ( l_asteriskModeEnabled == 1u )
         {
            /* Traitement du caractère '*' */
            l_result = mk_utils_handleAsterisk ( p_str, p_pattern, &l_currentPatternIndex, &l_nextPatternIndex, &l_asteriskModeEnabled );

            /* On passe au prochain caractère de la chaine */
            p_str++;
         }

         /* Sinon */
         else
         {
            /* Si le caractère spécial '?' est présent dans le pattern */
            if ( ( p_pattern [ l_currentPatternIndex ] == '?' ) && ( l_asteriskModeEnabled == 0 ) )
            {
               /* '?' : un seul caractère quelconque. */
               /* On passe au prochain caractère du pattern et de la chaine */
               l_currentPatternIndex = ( uint32_t ) l_currentPatternIndex + 1u;
               p_str++;
            }

            /* Sinon si le caractère spécial '#' est présent dans le pattern ' */
            else if ( ( p_pattern [ l_currentPatternIndex ] == '#' ) && ( l_asteriskModeEnabled == 0 ) )
            {
               /* Traitement du caractère '#' */
               /* '#' : un seul digit (0 à 9). */
               l_result = mk_utils_handleHashTag ( p_str, &l_currentPatternIndex );
               /* On passe au prochain caractère de la chaine */
               p_str++;
            }

            /* Sinon si le caractère spécial '*' est présent dans le pattern */
            else if ( ( p_pattern [ l_currentPatternIndex ] == '*' ) && ( l_asteriskModeEnabled == 0 ) )
            {
               /* Zéro ou plus caractères quelconques peuvent être présent */
               l_asteriskModeEnabled = mk_utils_enabledAsteriskMode ( p_pattern, &l_currentPatternIndex, &l_nextPatternIndex );
               /* On n'incrémente pas le pointeur p_str. */
            }

            /* Sinon si le caractère spécial '[' est présent dans le pattern */
            else if ( ( p_pattern [ l_currentPatternIndex ] == '[' ) && ( l_asteriskModeEnabled == 0 ) )
            {
               /* [charlist]  : un seul caractère dans la liste. */
               /* [!charlist] : un seul caractère qui n'est pas dans la liste. */
               /* On passe au prochain caractère du pattern */
               l_currentPatternIndex = ( uint32_t ) l_currentPatternIndex + 1u;
               l_result = mk_utils_handleBracket ( p_str, p_pattern, &l_currentPatternIndex );

               /* On passe au prochain caractère du pattern et de la chaine */
               l_currentPatternIndex = ( uint32_t ) l_currentPatternIndex + 1u; /* Gestion ']' ou '\0' */
               p_str++;
            }

            /* Sinon */
            else
            {
               /* Traitement des caractères affichables */
               l_result = mk_utils_handleDefault ( p_str, p_pattern, &l_currentPatternIndex );
               p_str++;
            }
         }
      }

      /* La chaine de caractères a été entièrement parcouru ou une différence existe entre les chaines. */
      /* Dans la première situation, il faut vérifier que le pattern a aussi été entièrement traité. */
      /* Traitement de la fin du pattern */
      l_result = mk_utils_handlePattern ( p_pattern, l_currentPatternIndex, l_result );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


