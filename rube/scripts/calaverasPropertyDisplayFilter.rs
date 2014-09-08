//
// You can use these functions to customize which properties are shown
// in the properties panel for an item. Each function gives you the item
// and a property name, and the function should return true if that item
// should be displayed.
//
//     shouldDisplayProperty : return true to display the property for the item
//
// Uncomment the functions below as necessary to customize your display.
// Do not change the callsign of the functions, or they will be ignored.
//
// If functions are left commented out, the default is to display the property.
//


// ========== World property display ==========
/*
bool shouldDisplayProperty( world w, const string& in propertyName ) {
    return true;
}
*/
// ========== Body property display ==========
bool shouldDisplayProperty( body b, const string& in propertyName ) {
  if (propertyName == "bullet" ||
    propertyName == "fixedRotation" ||
    propertyName == "sleepingAllowed" ||
    propertyName == "linearDamping" ||
    propertyName == "angularDamping" ||
    propertyName == "mass" ||
    propertyName == "gravityScale" ||
    propertyName == "linearVelocity" ||
    propertyName == "angularVelocity" ||
    propertyName == "awake")
      return b.getType() != 0;

  bool shouldDisplay = true;
  if (propertyName == "category" ||
    propertyName == "material" ||
    propertyName == "capacity" ||
    propertyName == "interval" ||
    propertyName == "isOpen" ||
    propertyName == "useOpenTimer" ||
    propertyName == "openTimer" || 
    propertyName == "forceMinDistance" ||
    propertyName == "forceMaxDistance" ||
    propertyName == "forceMaxAngle" ||
    propertyName == "forceMinAngularImpulse" ||
    propertyName == "forceMaxAngularImpulse" ||
    propertyName == "active") {
    shouldDisplay = false;
  }

  // Area
  if ( b.getCustomString( 'category' ) == 'area' ) {
    if (propertyName == "category" ||
        propertyName == "material") {
      shouldDisplay = true;
    }
  }

  // Entry
  if ( b.getCustomString( 'category' ) == 'entry' ) {
    if (propertyName == "category" ||
        propertyName == "capacity" ||
      propertyName == "interval" ||
      propertyName == "isOpen" ||
      propertyName == "useOpenTimer" ||
      propertyName == "openTimer" || 
      propertyName == "forceMinDistance" ||
      propertyName == "forceMaxDistance" ||
      propertyName == "forceMaxAngle" ||
      propertyName == "forceMinAngularImpulse" ||
      propertyName == "forceMaxAngularImpulse") {
      shouldDisplay = true;
    }
  }

  // Exit
  if ( b.getCustomString( 'category' ) == 'exit' ) {
    if (propertyName == "category" ||
        propertyName == "capacity" ||
        propertyName == "isOpen" ||
        propertyName == "useOpenTime" ||
        propertyName == "openTimer") {
        shouldDisplay = true;
    }
  }

  // Gravitron
  if ( b.getCustomString( 'category' ) == 'gravitron' ) {
    if (propertyName == "category" ||
        propertyName == "active") {
      shouldDisplay = true;
    }
  }

  // Level
  if ( b.getCustomString( 'category' ) == 'level' ) {
    if (propertyName == "category" ||
        propertyName == "level" ||
        propertyName == "inactive" ||
        propertyName == "active") {
      shouldDisplay = true;
    }
  }

  return shouldDisplay;
}

// ========== Fixture property display ==========
/*
bool shouldDisplayProperty( fixture f, const string& in propertyName ) {
    return true;
}
*/
// ========== Joint property display ==========
/*
bool shouldDisplayProperty( joint j, const string& in propertyName ) {
    return true;
}
*/
// ========== Image property display ==========
/*
bool shouldDisplayProperty( image i, const string& in propertyName ) {
    return true;
}
*/
// ========== Sampler property display ==========
/*
bool shouldDisplayProperty( sampler i, const string& in propertyName ) {
    return true;
}
*/


// ==========================
// This is to stop the auto-compile of the script panel
// from detecting errors that are not really errors.
void main(){}
