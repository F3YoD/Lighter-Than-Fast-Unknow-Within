#ifndef _COMBAT_H
#define _COMBAT_H

#include <stdio.h>
#include <stdbool.h>

#include "shared.h"
#include "rules.h"
#include "tools.h"
#include "ships.h"

enum combat_choice { COMBAT_ATTACK, COMBAT_REPAIR, COMBAT_FLEE, NB_CHOICES_COMBAT };
enum shop_choice { SHOP_HEALTH, SHOP_SCRAPS, SHOP_LEAVE, NB_CHOICES_SHOP };

void shoot(ship_t *, ship_t *, unsigned short);
void repair(ship_t *, int);
void flee(ship_t *);
void exchange(ship_t *, ship_t *, struct belongings);
void loot(ship_t *, ship_t *);
void destroy(ship_t **);

void be_sad(ship_t *);
void be_happy(ship_t *);
void be_angry(ship_t *);

#endif /* _COMBAT_H */
