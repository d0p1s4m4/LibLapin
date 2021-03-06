// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

/*
** BlendMode:
**  color source factor
**  color destination factor
**  color blend equation
**
**  alpha source factor
**  alpha destination factor
**  alpha blend equation
**
*/

#include			"lapin_private.h"

void				merge_clothe(t_bunny_map		*nod,
					     void			*pnw);

#define				PATTERN				\
  "%p target, %p source, %p position (%d, %d), %p shader"

void				bunny_blit(t_bunny_buffer		*output,
					   const t_bunny_clipable	*picture,
					   const t_bunny_position	*pos)
{
  bunny_blit_shader(output, picture, pos, NULL);
}

void				bunny_blit_shader(t_bunny_buffer	*output,
						  const t_bunny_picture	*picture,
						  const t_bunny_position *pos,
						  const t_bunny_shader	*_shader)
{
  t_bunny_position		defaul = {0, 0};

  if (pos == NULL)
    {
      defaul.x = picture->position.x;
      defaul.y = picture->position.y;
      pos = &defaul;
    }

  size_t			*type = (size_t*)output;
  size_t			*input_type = (size_t*)picture;
  sf::Shader			*shader = (sf::Shader*)_shader;
  sf::Sprite			*spr;
  sf::Texture			_txt;
  sf::Sprite			_spr;

  switch (*input_type)
    {
    case GRAPHIC_TEXT:
    case TTF_TEXT:
      {
	size_t			typ = *input_type;

	*input_type = GRAPHIC_RAM;
	bunny_blit_shader(output, picture, pos, _shader);
	*input_type = typ;
	scream_log_if
	  (PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
	return ;
      }
    case DRESSED_SPRITE:
      {
	struct bunny_dressed_sprite *spr = (struct bunny_dressed_sprite*)picture;
	std::map<int, std::list<t_bunny_clipable*> > clo;
	t_bunny_map **node;

	spr->type = (size_t)SPRITE;
	bunny_blit_shader(output, picture, pos, _shader);
	spr->type = (size_t)DRESSED_SPRITE;
	for (bunny_map_all(spr->clothes, node))
	  {
	    t_bunny_map *nod = *node;
	    size_t key = (size_t)nod->key;
	    t_bunny_clothe *clothe = (t_bunny_clothe*)nod->data;
	    t_bunny_closet *closet = bunny_map_get_data(spr->closets, key, t_bunny_closet*);

	    clo[closet->depth].push_back(&clothe->sprite->clipable);
	  }
	for (auto it = clo.begin(); it != clo.end(); ++it)
	  for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
	    bunny_blit_shader(output, *jt, pos, _shader);
	return ;
      }
    case TILEMAP:
      {
	struct bunny_tilemap	*tmap = (struct bunny_tilemap*)picture;

	tmap->working->rotation = tmap->tile_rotation;
	tmap->type = GRAPHIC_RAM;
	bunny_blit((t_bunny_buffer*)tmap, tmap->working, NULL);
	tmap->type = TILEMAP;
	// NO BREAK -> Graphic ram scope is needed too.
	[[fallthrough]];
      }
    case PARALLAX:
    case SPRITE:
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)picture;
	sf::IntRect		rect;

	rect.left = pic->rect.x;
	rect.top = pic->rect.y;
	rect.width = pic->rect.w;
	rect.height = pic->rect.h;
	pic->texture->setSmooth(pic->smooth);
	pic->texture->setRepeated(pic->mosaic);
	pic->tex = &pic->texture->getTexture();
	pic->sprite->setTexture(*pic->tex);
	pic->sprite->setTextureRect(rect);
	pic->sprite->setPosition(pos->x, pos->y);
	pic->sprite->setOrigin(pic->origin.x, pic->origin.y);
	pic->sprite->setScale(pic->scale.x, pic->scale.y);
	pic->sprite->setRotation(pic->rotation);
	pic->sprite->setColor
	  (sf::Color(pic->color_mask.argb[RED_CMP],
		     pic->color_mask.argb[GREEN_CMP],
		     pic->color_mask.argb[BLUE_CMP],
		     pic->color_mask.argb[ALPHA_CMP]
		     ));
	spr = pic->sprite;
	break ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*pic = (struct bunny_pixelarray*)picture;
	sf::IntRect		rect;
	int			i;
	int			j;

	rect.left = pic->rect.x;
	rect.top = pic->rect.y;
	rect.width = pic->rect.w;
	rect.height = pic->rect.h;
	for (j = picture->clip_y_position; j < picture->clip_y_position + picture->clip_height; ++j)
	  for (i = picture->clip_x_position; i < picture->clip_x_position + picture->clip_width; ++i)
	    if (i >= 0 && j >= 0 && i < picture->buffer.width && j < picture->buffer.height)
	      {
		unsigned int	c = pic->rawpixels[i + j * pic->width];

		pic->image->setPixel
		  (i, j,
		   sf::Color
		   ((c >> (RED_CMP * 8)) & 0xFF,
		    (c >> (GREEN_CMP * 8)) & 0xFF,
		    (c >> (BLUE_CMP * 8)) & 0xFF,
		    (c >> (ALPHA_CMP * 8)) & 0xFF
		    )
		 );
	      }
	pic->tex->loadFromImage(*pic->image, rect);
	pic->sprite->setPosition(pos->x, pos->y);
	if (gl_full_blit)
	  {
	    pic->sprite->setOrigin(pic->origin.x, pic->origin.y);
	    pic->sprite->setScale(pic->scale.x, pic->scale.y);
	    pic->sprite->setRotation(pic->rotation);
	    pic->sprite->setColor
	      (sf::Color(pic->color_mask.argb[RED_CMP],
			 pic->color_mask.argb[GREEN_CMP],
			 pic->color_mask.argb[BLUE_CMP],
			 pic->color_mask.argb[ALPHA_CMP]
			 ));
	    pic->tex->setSmooth(pic->smooth);
	    pic->tex->setRepeated(pic->mosaic);
	  }
	pic->sprite->setTexture(*pic->tex, true);
	spr = pic->sprite;
	break ;
      }
    default:
      scream_error_if
	(return, EINVAL, PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
    }

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*out = (struct bunny_window*)output;

	if (*input_type == GRAPHIC_RAM
	    || *input_type == SPRITE
	    || *input_type == TTF_TEXT
	    || *input_type == DRESSED_SPRITE)
	  {
	    if (shader)
	      out->window->draw(*spr, shader);
	    else
	      out->window->draw(*spr);
	  }
	else if (gl_full_blit == false)
	  out->window->draw(*spr, sf::RenderStates(sf::BlendNone));
	else
	  out->window->draw(*spr);
	scream_log_if
	  (PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
	return ;
      }
    case TILEMAP:
      {
	struct bunny_tilemap	*out = (struct bunny_tilemap*)output;

	__bunny_blit_tilemap(out, picture, pos, _shader);
	return ;
      }
    case TTF_TEXT:
    case DRESSED_SPRITE:
    case SPRITE:
    case GRAPHIC_TEXT:
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*out = (struct bunny_picture*)output;

	if (out->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)out);
	if (*input_type == GRAPHIC_RAM
	    || *input_type == SPRITE
	    || *input_type == TTF_TEXT
	    || *input_type == DRESSED_SPRITE)
	  {
	    if (shader)
	      {
		if (gl_set_alpha_blit)
		  {
		    sf::RenderStates stt = sf::BlendMultiply;

		    stt.shader = shader;
		    out->texture->draw(*spr, stt);
		  }
		if (gl_set_additional_blit)
		  {
		    sf::RenderStates stt = sf::BlendAdd;

		    stt.shader = shader;
		    out->texture->draw(*spr, stt);
		  }
		else if (gl_full_blit == false)
		  {
		    sf::RenderStates stt = sf::BlendNone;

		    stt.shader = shader;
		    out->texture->draw(*spr, stt);
		  }
		else
		  out->texture->draw(*spr, shader);
	      }
	    else if (gl_set_alpha_blit)
	      {
		sf::RenderStates stt = sf::BlendAlpha;

		stt.blendMode = sf::BlendMode
		  (sf::BlendMode::Zero, // Tuile
		   sf::BlendMode::One,  // Ombre
		   sf::BlendMode::Add,   // On garde la couleur de l'ombre
		   sf::BlendMode::One,  // Tuile
		   sf::BlendMode::One,   // Ombre
		   sf::BlendMode::ReverseSubtract // La tuile retire de la transparence
		   );
		out->texture->draw(*spr, stt);
	      }
	    else if (gl_set_additional_blit)
	      {
		sf::RenderStates stt = sf::BlendAdd;

		out->texture->draw(*spr, stt);
	      }
	    else if (gl_set_multiply_blit)
	      {
		sf::RenderStates stt = sf::BlendMultiply;

		out->texture->draw(*spr, stt);
	      }
	    else
	      {
		out->texture->draw(*spr);
	      }
	  }
	else if (gl_full_blit == false)
	  out->texture->draw(*spr, sf::RenderStates(sf::BlendNone));
	else
	  out->texture->draw(*spr);

	if (*type == SPRITE)
	  {
	    t_bunny_sprite *spr = (t_bunny_sprite*)picture;
	    const t_bunny_collision_shapes *col = bunny_sprite_get_collision(spr);

	    if (col)
	      for (unsigned int x = 0; x < col->nbr_collision; ++x)
		bunny_draw_collision_shape(output, &col->collisions[x], RED);
	  }

	scream_log_if
	  (PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*out = (struct bunny_pixelarray*)output;

	if (*input_type == SYSTEM_RAM)
	  {
	    const t_bunny_pixelarray	*pic = (const t_bunny_pixelarray*)picture;

	    if (gl_bunny_my_blit == NULL)
	      fprintf(stderr, "gl_bunny_my_blit is not set.");
	    else
	      {
		if (out->res_id != 0)
		  bunny_make_clipable_unique((t_bunny_clipable*)out);
		gl_bunny_my_blit((t_bunny_pixelarray*)out, pic, pos);
	      }
	  }
	else
	  {
	    // This function is an horrible mess
	    const bunny_pixelarray	*pic = (const bunny_pixelarray*)output;
	    sf::Image			img = spr->getTexture()->copyToImage();
	    int				i;
	    int				j;

	    if (pic->res_id != 0)
	      bunny_make_clipable_unique((t_bunny_clipable*)pic);
	    for (j = picture->clip_y_position;
		 j < picture->clip_y_position + picture->clip_height;
		 ++j)
	      for (i = picture->clip_x_position;
		   i < picture->clip_x_position + picture->clip_width;
		   ++i)
		{
		  t_bunny_position	posx;

		  posx.x = pos->x + i;
		  posx.y = pos->y + j;
		  if (posx.x >= 0 && posx.x < output->width &&
		      posx.y >= 0 && posx.y < output->height)
		    {
		      sf::Color		c = img.getPixel(i, j);
		      int		d = posx.x + posx.y * pic->width;

		      ((t_color*)pic->rawpixels)[d].argb[ALPHA_CMP] = c.a;
		      ((t_color*)pic->rawpixels)[d].argb[RED_CMP] = c.r;
		      ((t_color*)pic->rawpixels)[d].argb[GREEN_CMP] = c.g;
		      ((t_color*)pic->rawpixels)[d].argb[BLUE_CMP] = c.b;
		    }
		}
	  }
	scream_log_if
	  (PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
	return ;
      }
    default:
      scream_error_if
	(return, EINVAL, PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
    }
}
