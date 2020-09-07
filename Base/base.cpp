#include"base.h"
selectItem creatSelectItem(DataName _name,double _minValue,double _maxValue,bool _isChecked,bool _isInverse)
{
    selectItem Item;
    Item.name=_name;
    Item.maxValue=_maxValue;
    Item.minValue=_minValue;
    Item.isChecked=_isChecked;
    Item.isInverse=_isInverse;
    return Item;
}
