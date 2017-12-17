#include "game.h"

void game(SDL_Surface * pEcran, char pNom[20]){
// role : gere la partie jouable du jeu
//
// nb : la partie interface sera supprimé car jugé comme obsolète 
	int continuer = 1;
	SDL_Event ev;
	bool clique = false;
	bool clique2;	
	TTF_Init();
	printf("init ttf\n");
		
	// ========================= LOADING ======================== //
	fenetre_option_t fenetre_option;
	fond_t fond;
	barre_vie_t life;
	bar_shield_t shield;
	player_ship_t * my_ship = (player_ship_t *)malloc(sizeof(player_ship_t));

		// =============== TEST BATTLE ============= //
	// on cree un ennemi
	ship_t *enemy = (ship_t*)malloc(sizeof(ship_t));
	load_ship(enemy);
	SDL_Texture* img_enemy[15];
	int nb_img = 3, frame_time = 400, temps_actuel2 = 0, temps_precedent2 = 0;
	int current_img = 0;
	float scale = 10;

	img_enemy[0] = IMG_LoadTexture(renderer, "../assets/images/ship_enemy/ship_enemy1.0.png");
	img_enemy[1] = IMG_LoadTexture(renderer, "../assets/images/ship_enemy/ship_enemy1.1.png");
	img_enemy[2] = IMG_LoadTexture(renderer, "../assets/images/ship_enemy/ship_enemy1.2.png");
		
	SDL_Rect pos_enemy; pos_enemy.x = 690 / scale; pos_enemy.y = 120 / scale;

	int choi = CHOI_ATTAQUE; // le choi ou se pose le curseur en premier dans le
				 // le sous programme combat()
	int action = NE_FAIT_RIEN; // parametre obligatoir pour le sous programme de combat
	SDL_Rect pos_tir; pos_tir.x = 100; pos_tir.y = 400; 
			// postion initial de notre tir a donner au sous programme
			// combat ()

	bool my_turn = true; // est mit a vrai si c'est au tour du joueur

	// on cree un rayon enemy
	SDL_Rect rayon_enemy;
	rayon_enemy.x = 800;
	rayon_enemy.y = 300;
	rayon_enemy.w = 0;
	rayon_enemy.h = 10;
		// ========================================= //
		
	load_fenetre_option(&fenetre_option);
	load_fond(&fond);
	load_barre_vie(&life, 10, "../assets/images/lifebare2.png");
	load_bar_shield(&shield, 100, "../assets/images/shieldbare.png");
	load_player_ship(my_ship, pNom);
	
	team_t * team = (team_t *)malloc(sizeof(team_t));
	load_team(team);
	/**************************************************************/	

	// ====================  GESTION DU TEMPS ==================== //
	int temps_precedent = 0, temps_actuel = 0;
	/***************************************************************/ 

	int control = 0;
	while(continuer){
		SDL_PollEvent(&ev);
		switch(ev.type){
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym){
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_SPACE:
						if(control < team->taille - 1)
							control++;
						else 
							control = 0;
						break;
					case SDLK_TAB:
						clique = true;
						break;
				}
				break;
			case SDL_KEYUP:
				switch(ev.key.keysym.sym){
					case SDLK_TAB:
						if(clique){
							clique = false;
							if(fenetre_option.actif)
								fenetre_option.actif = false;
							else
								fenetre_option.actif = true;
						}
						break;
				}
				break;
			case SDL_QUIT:
				continuer = 0;
				break;
		}
		// ======================= GESTION DU TEMPS ==================== //
		temps_actuel2 = SDL_GetTicks();
		if (temps_actuel2 - temps_precedent2 > frame_time){
			if(current_img == nb_img - 1){
				current_img = 0;
			}else{
				current_img++;
			}
			temps_precedent2 = temps_actuel2;
		}



		temps_actuel = SDL_GetTicks();
		if (temps_actuel - temps_precedent > FRAME_TIME){
			if(my_ship->current_img < NB_IMAGE_SHIP_PLAYER - 1)
				my_ship->current_img++;
			else
				my_ship->current_img = 0;
			temps_precedent = temps_actuel;	
		}	
			// ==================== UPDATE ================== //
			update_fond(&fond);
			//update_barre_vie(&life);
			//update_bar_shield(&shield);
			update_player_ship(my_ship);
			update_team(team, ev, my_ship, control);
				// ====================== TEST BATTLE ==================== //

				// init flip pour changer l'angle du vaisseau ennemi
				SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
				
				// affichage du vaisseau enemy 
				SDL_QueryTexture(img_enemy, NULL, NULL, &pos_enemy.w, &pos_enemy.h);
				SDL_RenderCopyEx(renderer, img_enemy, NULL, &pos_enemy, 90, NULL, flip);
				
				update_ship(enemy); // petit sous programme qui affiche la barre de vie
						    // d'une structure ship_t
				/////////////////////////////////////////////////////////////
				
			//affichage du texte 
			//AfficherTexte("Bienvenue",police,couleur,posTexte);
			//SDL_RenderCopy( renderer, texturetexte, NULL, &posTexte);
			afficher_stat_ship(my_ship);
			init_menu_combat();
			combat(my_ship, enemy, &choi, ev, &clique2, &action, &pos_tir, &my_turn);
			if(!my_turn){
				attaque_rayon_enemy(&rayon_enemy, &my_turn, my_ship,enemy);
			}

		SDL_RenderSetScale(renderer, scale, scale);	
		SDL_QueryTexture(img_enemy[current_img], NULL, NULL, &pos_enemy.w, &pos_enemy.h);
		SDL_RenderCopy(renderer, img_enemy[current_img], NULL, &pos_enemy);
		SDL_RenderSetScale(renderer, 1, 1);	

			update_fenetre_option(&fenetre_option);
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			/**************************************************/
			
			//temps_precedent = temps_actuel;
		//}
		/******************************************************************/
	}
	
	///libération	
	TTF_Quit();
	//SDL_DestroyTexture(texturetexte);
	//printf("libération du ttf \n");
	freeTeam(team);
	
	SDL_DestroyTexture(img_enemy);
	free(enemy);	
	free_fond(&fond);
	free_barre_vie(&life);
	free_bar_shield(&shield);
	free_player_ship(my_ship);
	free_fenetre_option(&fenetre_option);

	free(team);
} 
