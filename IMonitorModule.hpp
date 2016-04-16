/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:40:02 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 15:55:40 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORMODULE_H
# define IMONITORMODULE_H

class IMonitorModule {
public:
	virtual IMonitorModule( bool is_widget ) = 0;
	virtual ~IMonitorModule( void ) {}
	virtual char getType( void ) = 0;
	virtual void swapHide( void ) = 0;
	virtual bool isHidden( void ) = 0;
	virtual void refresh( void ) = 0;
	virtual void toTerminal(int row, int height) = 0;
	virtual void toGraphic( void ) = 0;
};

#endif
