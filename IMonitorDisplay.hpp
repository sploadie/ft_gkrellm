/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorDisplay.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:30:51 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 16:48:25 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORDISPLAY_H
# define IMONITORDISPLAY_H

# include "IMonitorModule.hpp"

# include "NameModule.hpp"
# include "OsInfoModule.hpp"
# include "TimeModule.hpp"
# include "CPUModule.hpp"
# include "ProcModule.hpp"
# include "UsageModule.hpp"
# include "RAMModule.hpp"
# include "NetworkModule.hpp"
# include "PonyModule.hpp"

class IMonitorDisplay {
public:
	virtual ~IMonitorDisplay( void ) {}
	virtual int run( void ) = 0;
	virtual void addModules( std::string ) = 0;
};

#endif
