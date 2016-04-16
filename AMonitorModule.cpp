/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMonitorModule.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:07:47 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 19:31:38 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMonitorModule.hpp"

AMonitorModule::AMonitorModule(char type, bool has_widget) : _type(type), _show(true), _has_widget(has_widget) {}
AMonitorModule::~AMonitorModule( void ) {}
char AMonitorModule::getType( void ) { return this->_type; }
void AMonitorModule::swapHide( void ) { this->_show = (this->_show ? false : true); }
bool AMonitorModule::isHidden( void ) { return !this->_show; }
bool AMonitorModule::hasWidget( void ) { return this->_has_widget; }
