/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPUModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:50:52 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPUMODULE_H
# define CPUMODULE_H

# include "AMonitorModule.hpp"

class CPUModule : public AMonitorModule {

public:

	CPUModule( bool has_widget );

	~CPUModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );

private:
	CPUModule( void );
	CPUModule( CPUModule const & obj );
	CPUModule & operator=( CPUModule const & rhs );

	// Gtk::Box* _box;
	std::string _cpuinfo;
	Gtk::Label* _cpu_label;
};

#endif
