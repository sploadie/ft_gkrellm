/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMonitorModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:07:47 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 19:31:17 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMONITORMODULE_H
# define AMONITORMODULE_H

# include "IMonitorModule.hpp"

class AMonitorModule : public IMonitorModule {
public:
	AMonitorModule(char type, bool has_widget);
	virtual ~AMonitorModule( void );
	AMonitorModule & operator=( AMonitorModule const & rhs );

	char getType( void );
	void swapHide( void );
	bool isHidden( void );
	bool hasWidget( void );
	virtual void refresh( void ) = 0;
	virtual int toTerminal(int row, int height) = 0;
	virtual Gtk::Widget* getWidget( void ) = 0;

protected:
	char						_type;
	bool						_show;
	bool						_has_widget;
};

#endif
