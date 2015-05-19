/*
  ==============================================================================

    AnimatedListBox.h
    Created: 13 Apr 2015 11:26:11pm
    Author:  Adam Elemental

  ==============================================================================
*/

#ifndef ANIMATEDLISTBOX_H_INCLUDED
#define ANIMATEDLISTBOX_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <functional>

//==============================================================================

namespace AnimatedListBoxIds 
{
    static const Identifier data ("Data");
    static const Identifier node ("Node");
    static const Identifier title ("Title");
    static const Identifier description ("Description");
}

class AnimatedListBox    : public ListBox, public ListBoxModel 
{
public:
    AnimatedListBox(ValueTree data, std::function <void(int, ListBox*, ValueTree, const MouseEvent&)> itemClicked)
    :   ListBox("Animated ListBox", this), 
        data (data), 
        itemClicked (itemClicked) 
    {
        setModel (this);
        this->setRowHeight (50); // use proportionOfHeight plus min height, e.g. for retina screens
    }

    ~AnimatedListBox()
    {
    }

    int getNumRows() 
    {
        return data.getNumChildren ();
    }

    ValueTree getValueTreeForRow (int rowIndex)
    {
        return data.getChild (rowIndex);
    }
    
    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
    {
        return nullptr;
        
        // NoteRatioComponent *row = dynamic_cast<NoteRatioComponent*>(existingComponentToUpdate);
        //
        // DBG ( "getNumRows: " << getNumRows() );
        // if(rowNumber < getNumRows())
        // {
        //     if(!row)
        //     {
        //         DBG ("Creating new NoteRatioComponent:");
        //         row = new NoteRatioComponent (getValueTreeForRow (rowNumber), sharedObjects);
        //     }
        //
        //     else #<{(| Update all properties of your custom component with the data for the current row  |)}>#
        //     {
        //         DBG ("Updating NoteRatioComponent:");
        //         row->setNoteRatio (getValueTreeForRow (rowNumber));
        //     }
        //     // DBG (getValueTreeForRow (rowNumber).toXmlString());
        //
        // }
        // else
        // {
        //     // Nothing to display, free the custom component
        //     delete existingComponentToUpdate;
        //     row = nullptr;
        // }
        //
        //
        // return row;
    }

    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) 
    {
        g.fillAll (Colour (0xff001F36));
        
        g.setFont (Font (16.0f));
        g.setColour (Colours::white);
        g.drawText(getValueTreeForRow (rowNumber).getProperty (AnimatedListBoxIds::title), 0, 0, width, height, Justification::centred, true);
        if (rowIsSelected)
        {
            g.drawRect (getBounds());
        }
    }

    void listBoxItemClicked (int row, const MouseEvent &e)
    {
        DBG (data.getChild(row).toXmlString());
        if (itemClicked != nullptr) 
        {
            itemClicked (row, this, getValueTreeForRow(row), e);
        }
    }

private:
    ValueTree data;
    std::function <void(int, ListBox*, ValueTree, const MouseEvent&)> itemClicked;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnimatedListBox)
};


#endif  // ANIMATEDLISTBOX_H_INCLUDED