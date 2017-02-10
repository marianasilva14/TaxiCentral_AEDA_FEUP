/*
 * Menu.h
 *
 */

#pragma once

#include <vector>
#include <string>

#include "Customer.h"
#include "Service.h"
#include "Route.h"
#include "CentralTaxis.h"
#include "utilities.h"

using namespace std;

unsigned short int customersMenu(CentralTaxis &central);

unsigned short int customerMenuType(CentralTaxis &central);

unsigned short int oneCustomerMenu(CentralTaxis &central);

unsigned short int editCustomerMenu(CentralTaxis &central);

unsigned short int oneCustomerServicesMenu(CentralTaxis &central);

unsigned short int servicesMenu(CentralTaxis &central);

unsigned short int routesMenu(CentralTaxis &central);

unsigned short int mainMenu(CentralTaxis &central);
