/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorDisplay.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:30:51 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 19:32:16 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORDISPLAY_H
# define IMONITORDISPLAY_H

# include "IMonitorModule.hpp"

#include "NameModule.hpp"

class IMonitorDisplay {
public:
	virtual ~IMonitorDisplay( void ) {}
	virtual int run( void ) = 0;
	virtual void addModules( std::string ) = 0;
};

#endif
