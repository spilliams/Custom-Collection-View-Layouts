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
} SWCollectionViewLineLayoutAttributeSide;

NS_CLASS_AVAILABLE_IOS(6_0) @interface SWCollectionViewLineLayoutAttributes : UICollectionViewLayoutAttributes
@property (nonatomic) SWCollectionViewLineLayoutAttributeSide side;
@end
