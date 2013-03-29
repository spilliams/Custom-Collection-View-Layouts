//
//  SWCollectionViewLineLayout.h
//  SWCollectionViewLineLayout
//
//  Created by Spencer Williams on 3/14/13.
//  Copyright (c) 2013 Spencer Williams. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SWCollectionViewLineLayoutAttributes.h"

/// @name Constants

/// The cell's supplementary view for its tail--that is, the view between the cell itself and the grip
static NSString* const kSWSupplementaryViewKindItemTail = @"itemTail";
/// The cell's supplementary view for its grip--that is, the view that "binds" the cell to the line
static NSString* const kSWSupplementaryViewKindItemGrip = @"itemGrip";
/// The cell's supplementary view for its line label. This view pins to the line
static NSString* const kSWSupplementaryViewKindItemLineLabel = @"cellLineLabel";
/// A section header view
static NSString* const kSWSupplementaryViewKindSectionHeader = @"sectionHeader";
/// A section footer view
static NSString* const kSWSupplementaryViewKindSectionFooter = @"sectionFooter";

typedef enum {
    SWCollectionViewLineLayoutTypeLeft,
    SWCollectionViewLineLayoutTypeRight,
    SWCollectionViewLineLayoutTypeBoth
} SWCollectionViewLineLayoutType;

@protocol SWCollectionViewDelegateLineLayout <UICollectionViewDelegateFlowLayout>

@end

@protocol SWCollectionViewDataSourceLineLayout <UICollectionViewDataSource>

- (SWCollectionViewLineLayoutAttributeSide)sideForItemAtIndexPath:(NSIndexPath *)indexPath;

@end

NS_CLASS_AVAILABLE_IOS(6_0) @interface SWCollectionViewLineLayout : UICollectionViewFlowLayout
@property (nonatomic) SWCollectionViewLineLayoutType type;
@end
