/*!
	@file
	@author		Albert Semenov
	@date		07/2012
*/

#include "Precompiled.h"
#include "PropertyPanelControl.h"
#include "FactoryManager.h"

namespace tools
{

	FACTORY_ITEM_ATTRIBUTE(PropertyPanelControl)

	PropertyPanelControl::PropertyPanelControl() :
		mCurrentData(nullptr),
		mDistance(0)
	{
	}

	PropertyPanelControl::~PropertyPanelControl()
	{
	}

	void PropertyPanelControl::OnInitialise(Control* _parent, MyGUI::Widget* _place, const std::string& _layoutName)
	{
		Control::OnInitialise(_parent, _place, _layoutName);

		mDistance = MyGUI::utility::parseValue<int>(mMainWidget->getUserString("HeightDistance"));
	}

	void PropertyPanelControl::HideControls()
	{
		for (VectorPairControl::iterator control = mPropertyControls.begin(); control != mPropertyControls.end(); control ++)
		{
			(*control).second->setProperty(nullptr);
			(*control).second->getRoot()->setVisible(false);
		}
	}

	void PropertyPanelControl::InitialiseProperty(PropertyPtr _property, int& _height)
	{
		std::string type = _property->getType()->getType();
		PropertyControl* control = nullptr;

		for (VectorPairControl::iterator child = mPropertyControls.begin(); child != mPropertyControls.end(); child ++)
		{
			if ((*child).first == type && !(*child).second->getRoot()->getVisible())
			{
				control = (*child).second;
				control->getRoot()->setVisible(true);
				break;
			}
		}

		if (control == nullptr)
		{
			control = components::FactoryManager::GetInstance().CreateItem<PropertyControl>(_property->getType()->getType());
			if (control != nullptr)
			{
				control->Initialise(this, mMainWidget, "");

				mPropertyControls.push_back(std::make_pair(_property->getType()->getType(), control));
			}
		}

		if (control != nullptr)
		{
			control->setProperty(_property);
			control->getRoot()->setPosition(0, _height);

			_height += control->getRoot()->getHeight() + mDistance;
		}
	}

	void PropertyPanelControl::setCurrentData(DataPtr _data)
	{
		mCurrentData = _data;

		HideControls();

		if (mCurrentData != nullptr)
		{
			int height = 0;
			const DataType::VectorProperty& properties = mCurrentData->getType()->getProperties();
			for (DataType::VectorProperty::const_iterator property = properties.begin(); property != properties.end(); property ++)
			{
				if ((*property)->getVisible())
				{
					PropertyPtr pr = mCurrentData->getProperty((*property)->getName());
						InitialiseProperty(pr, height);
				}
			}
		}
	}

}
