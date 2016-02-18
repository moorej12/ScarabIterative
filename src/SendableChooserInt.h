/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011-2016. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef __SENDABLE_CHOOSER_INT_H__
#define __SENDABLE_CHOOSER_INT_H__

#include "SmartDashboard/Sendable.h"
#include "tables/ITable.h"
#include <map>
#include <memory>
#include <string>

class SendableChooserInt : public Sendable {
	public:
		SendableChooserInt();
		~SendableChooserInt();

		void AddObject(const std::string &name, int object);
		void AddDefault(const std::string &name, int object);
		int GetSelected();
		void InitTable(std::shared_ptr<ITable> subtable);
		std::shared_ptr<ITable> GetTable() const;
		std::string GetSmartDashboardType() const;

	private:
		std::string m_defaultChoice;
		std::map<std::string, int > m_choices;
		std::shared_ptr<ITable> m_table;
};

#endif
