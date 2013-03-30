//
//  SWCollectionViewLineLayoutAttributes.h
//  SWCollectionViewLineLayout
//
//  Created by Spencer Williams on 3/14/13.
//  Copyright (c) 2013 spilliams. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum {
    SWCollectionViewLineLayoutAttributeSideLeft,
    SWCollectionViewLineLayoutAttributeSideRight,
    SWCollectionViewLineLayoutAttributeSideEither,
    SWCollectionViewLineLayoutAttributeSideBoth,
} SWCollectionViewLineLayoutAttributeSide;

/** A subclass of UICollectionViewLayoutAttributes that provides extra support
 for SWCollectionViewLineLayout
 
 **Table 1** Description of side values
 
 Constant                                        | Description
 ------------------------------------------------|-----------------------------------------------------------------
 `SWCollectionViewLineLayoutAttributeSideLeft`   | The item is on the left side of the line
 `SWCollectionViewLineLayoutAttributeSideRight`  | The item is on the right side of the line
 `SWCollectionViewLineLayoutAttributeSideEither` | The item is on one side of the line, as determined by the layout
 `SWCollectionViewLineLayoutAttributeSideBoth`   | The item spans both sides of the line
 
 */
NS_CLASS_AVAILABLE_IOS(6_0) @interface SWCollectionViewLineLayoutAttributes : UICollectionViewLayoutAttributes
/// The side the item is on.
@property (nonatomic) SWCollectionViewLineLayoutAttributeSide side;
@end
