//
//  SWCollectionViewLineLayout.h
//  SWCollectionViewLineLayout
//
//  Created by Spencer Williams on 3/29/13.
//  Copyright (c) 2013 spilliams. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SWCollectionViewLineLayoutAttributes.h"

/// @name Constants

/// The cell's supplementary view for its tail--that is, the view between the cell itself and the grip
static NSString* const kSWSupplementaryViewKindItemTail = @"itemTail";
/// The cell's supplementary view for its grip--that is, the view that "binds" the cell to the line
static NSString* const kSWSupplementaryViewKindItemGrip = @"itemGrip";
/// The cell's supplementary view for its line label. This view pins to the line
static NSString* const kSWSupplementaryViewKindItemLineLabel = @"itemLineLabel";
/// A section header view
static NSString* const kSWSupplementaryViewKindSectionHeader = @"sectionHeader";
/// A section footer view
static NSString* const kSWSupplementaryViewKindSectionFooter = @"sectionFooter";

/** Members conforming to this protocol are responsible for providing data on
 Line-Layout-specific data, such as "which side does in item at this index path
 lie on?"
 */
@protocol SWCollectionViewDataSourceLineLayout <UICollectionViewDataSource>
@optional
/** The layout asks its data source which side of the line an item is on.
 @param indexPath The index path of the item.
 @return The side of the line the item lies on.
 */
- (SWCollectionViewLineLayoutAttributeSide)sideForItemAtIndexPath:(NSIndexPath *)indexPath;

@end

/** A Line Layout presents a collection of items all tied to one line that 
 extends either horizontally or vertically with respect to the view. The view
 may scroll in the axial direction, but not in the other direction.
 
 ###Layout DSL
 
 A Line Layout inherits several concepts from the FLow Layout that comes with
 iOS 6.
 
 **Table 1** How properties in UICollectionViewFlowLayout map to
 SWCollectionViewLineLayout
 
 Property                | Flow Layout                                                    | Line Layout
 ------------------------|----------------------------------------------------------------|------------------------------
 scrollDirection         | The scroll direction of the grid.                              | No change
 sectionInset            | The margins used to lay out content in a section               | No change
 minimumLineSpacing      | The minimum spacing to use between lines of items in the grid. | **Not used**. See below
 minumumInterItemSpacing | The minimum spacing to use between items in the same row.      | Slightly different. See below.
 itemSize                | The default size to use for cells                              | No change
 headerReferenceSize     | The default sizes to use for section headers.                  | No change
 footerReferenceSize     | The default sizes to use for section footers.                  | No change</table>
 
 ####Line Spacing
 
 Since there is no concept of a "row" in a Line Layout, there is no need for a 
 `minimumLineSpacing`. This property is simply unused in this layout.
 
 ####Item Spacing
 
 `minimumInterItemSpacing` represents the minimum distance between a "grip" and 
 whatever's next on the line (another grip, a lineLabel, the end of the section,
 etc). Note that this retains its "minimum" meaning since the distance between
 two grips may be greater than this value--for instance if the first item is
 very tall, or if it spans across both sides and thus covers up the line 
 entirely.
 
 The distance between the item and the line is derived from the view's size,
 the section's inset, and the item's size. If this derived value is greater than 
 the maximumLineItemSpacing, that property's value is instead used. Note that 
 `maximumLineItemSpacing` has no effect on items with side attribute
 `SWCollectionViewLineLayoutAttributeSideBoth`.
 
 ####Item Side
 
 An item may be on the left side of the line, the right, both sides (it will be 
 twice as wide as other cells), or either side—in which case the layout will 
 place it into whatever side makes more sense.
 
 ###Supplementary Views
 
 **Table 2** Line Layout Supplementary View Kinds
 
 Constant                                | Value           | Description
 ----------------------------------------|-----------------|------------------------------------
 `kSWSupplementaryViewKindItemTail`      | "itemTail"      | A view between the cell and the grip. Usually arrow-shaped.
 `kSWSupplementaryViewKindItemGrip`      | "itemGrip"      | A view that appears to bind the tail to the line.
 `kSWSupplementaryViewKindItemLineLabel` | "itemLineLabel" | A view bound to the line just above the grip.
 `kSWSupplementaryViewKindSectionHeader` | "sectionHeader" | A section header view.
 `kSWSupplementaryViewKindSectionFooter` | "sectionFooter" | A section footer view.</table>
 
 ###Decoration View Kinds
 
 Since decoration views are managed entirely by the layout, there are no 
 delegate or data source methods asking for them. Instead, the decoration views
 are manipulated via setting properties on the layout.
 
 **Table 3** Line Layout Decoration View Kinds
 
 Property   | Default value  | Description
 -----------|----------------|---------------------
 lineImage  | `nil`          | The image used for the line. If nil, the decoration view is derived from the lineColor and lineThickness properties
 arrowImage | `nil`          | The image used for the arrows.
 
 
 */
NS_CLASS_AVAILABLE_IOS(6_0) @interface SWCollectionViewLineLayout : UICollectionViewFlowLayout


/// ----------------------------------------------------------------------------
/// @name Manipulate Item Attributes
/// ----------------------------------------------------------------------------
/** The default side to put .
 
 Setting this will determine which side of the line items
 are put on if the layout's data source does not implement
 -sideForItemAtIndexPath:
 */
@property (nonatomic) SWCollectionViewLineLayoutAttributeSide itemSide;
/// The maximum amount of space between the line and an item
@property (nonatomic) CGFloat maximumLineItemSpacing;

/// ----------------------------------------------------------------------------
/// @name Manipulate Decoration Views
/// ----------------------------------------------------------------------------
/** The image to use for the line decoration view
 
 If `nil`, the line is generated from the lineColor and lineWidth properties.
 */
@property (nonatomic, strong) UIImage *lineImage;
/** The color to use for the line and arrows.

 Unnecessary for line if lineImage is not `nil`. Unnecessary for arrows if 
 arrowImage is not `nil`.
 */
@property (nonatomic, strong) UIColor *lineColor;
/** The thickness to use for the line and arrows.
 
 Unnecessary for line if lineImage is not `nil`. Unnecessary for arrows if
 arrowImage is not `nil`.
 */
@property (nonatomic) CGFloat lineThickness;
/** The image to use for the arrow decoration views.
 
 Note that this property should be set to the image for the down arrow, and the
 view for the up arrow will be derived from that.
 
 If `nil` and displayArrows is set to `YES`, arrows will be generated from the
 lineColor and lineWidth properties.
 */
@property (nonatomic, strong) UIImage *arrowImage;
/// Whether or not to display arrows at either end of the line to denote that
/// there are items off-screen.
@property (nonatomic) BOOL displayArrows;
@end
