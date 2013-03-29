//
//  SWCollectionViewLineLayout.m
//  SWCollectionViewLineLayout
//
//  Created by Spencer Williams on 3/29/13.
//  Copyright (c) 2013 spilliams. All rights reserved.
//

#import "SWCollectionViewLineLayout.h"
#import "SWCollectionViewLineLayoutAttributes.h"

static NSString* const kSWLineLayoutSectionDictionaryKeyItems = @"items";
static NSString* const kSWLineLayoutSectionDictionaryKeyHeader = @"header";

@interface SWCollectionViewLineLayout()
@property (strong, nonatomic) NSMutableArray *layoutData;
- (CGFloat)lengthForSectionAtIndex:(NSInteger)index;
@end

static NSString* const kSWDecorationViewKindLine = @"line";

@implementation SWCollectionViewLineLayout

- (id)init
{
    if (self = [super init]) {
        [self setType:SWCollectionViewLineLayoutTypeBoth];
    }
    return self;
}

+ (Class)layoutAttributesClass
{
    return [SWCollectionViewLineLayoutAttributes class];
}

- (void)prepareLayout
{
    [super prepareLayout]; // since we're a subclass of UICollectionViewFlowLayout
    
    id<UICollectionViewDelegateFlowLayout> delegate = (id<UICollectionViewDelegateFlowLayout>)self.collectionView.delegate;
    BOOL delegateIsDelegateFlowLayout = [delegate conformsToProtocol:@protocol(UICollectionViewDelegateFlowLayout)];
    
    NSInteger numSections = 1;
    if ([self.collectionView.dataSource respondsToSelector:@selector(numberOfSectionsInCollectionView:)]) {
        numSections = [self.collectionView.dataSource numberOfSectionsInCollectionView:self.collectionView];
    }
    [self setLayoutData:[NSMutableArray arrayWithCapacity:numSections]];
    
    for (int section=0; section<numSections; section++) {
        NSMutableDictionary *sectionDictionary = [NSMutableDictionary new];
        
        UIEdgeInsets sectionInset = [self sectionInset];
        if (delegateIsDelegateFlowLayout &&
            [delegate respondsToSelector:@selector(collectionView:layout:insetForSectionAtIndex:)]) {
            sectionInset = [delegate collectionView:self.collectionView layout:self.collectionView.collectionViewLayout insetForSectionAtIndex:section];
        }
        if (self.scrollDirection == UICollectionViewScrollDirectionHorizontal) {
            [sectionDictionary setObject:[NSNumber numberWithFloat:sectionInset.left] forKey:@"insetLeading"];
            [sectionDictionary setObject:[NSNumber numberWithFloat:sectionInset.right] forKey:@"insetTrailing"];
        } else {
            [sectionDictionary setObject:[NSNumber numberWithFloat:sectionInset.top] forKey:@"insetLeading"];
            [sectionDictionary setObject:[NSNumber numberWithFloat:sectionInset.bottom] forKey:@"insetTrailing"];
        }
        
        CGSize headerSize = self.headerReferenceSize;
        CGSize footerSize = self.footerReferenceSize;
        if (delegateIsDelegateFlowLayout &&
            [delegate respondsToSelector:@selector(collectionView:layout:referenceSizeForHeaderInSection:)]) {
            headerSize = [delegate collectionView:self.collectionView layout:self.collectionView.collectionViewLayout referenceSizeForHeaderInSection:section];
        }
        if (delegateIsDelegateFlowLayout &&
            [delegate respondsToSelector:@selector(collectionView:layout:referenceSizeForFooterInSection:)]) {
            footerSize = [delegate collectionView:self.collectionView layout:self.collectionView.collectionViewLayout referenceSizeForFooterInSection:section];
        }
        
        if (self.scrollDirection == UICollectionViewScrollDirectionHorizontal) {
            [sectionDictionary setObject:[NSNumber numberWithFloat:headerSize.width] forKey:@"headerLength"];
            [sectionDictionary setObject:[NSNumber numberWithFloat:footerSize.width] forKey:@"footerLength"];
        } else {
            [sectionDictionary setObject:[NSNumber numberWithFloat:headerSize.height] forKey:@"headerLength"];
            [sectionDictionary setObject:[NSNumber numberWithFloat:footerSize.height] forKey:@"footerLength"];
        }
        
        NSInteger numItems = 0;
        if ([self.collectionView.dataSource respondsToSelector:@selector(collectionView:numberOfItemsInSection:)]) {
            numItems = [self.collectionView.dataSource collectionView:self.collectionView numberOfItemsInSection:section];
        }
        NSMutableArray *items = [NSMutableArray arrayWithCapacity:numItems];
        for (int row=0; row<numItems; row++) {
            NSMutableDictionary *item = [NSMutableDictionary new];
            
            CGSize itemSize = [self itemSize];
            if (delegateIsDelegateFlowLayout &&
                [self.collectionView.delegate respondsToSelector:@selector(collectionView:layout:sizeForItemAtIndexPath:)]) {
                itemSize = [delegate collectionView:self.collectionView
                                             layout:self
                             sizeForItemAtIndexPath:[NSIndexPath indexPathForItem:row
                                                                        inSection:section]];
            }
            // we only care about one dimension of the item's size
            if (self.scrollDirection == UICollectionViewScrollDirectionHorizontal) {
                [item setObject:[NSNumber numberWithFloat:itemSize.width] forKey:@"length"];
            } else {
                [item setObject:[NSNumber numberWithFloat:itemSize.height] forKey:@"length"];
            }
            
            [items addObject:item];
            
        } // items loop
        [sectionDictionary setObject:items forKey:@"items"];
        
    } // sections loop
}

// Subclasses must override this method and use it to return the width and height of the collection view’s content. These values represent the width and height of all the content, not just the content that is currently visible. The collection view uses this information to configure its own content size to facilitate scrolling.
- (CGSize)collectionViewContentSize
{
    CGSize contentSize = CGSizeZero;
    if (self.scrollDirection == UICollectionViewScrollDirectionVertical) {
        contentSize.width = self.collectionView.bounds.size.width;
    } else {
        contentSize.height = self.collectionView.bounds.size.height;
    }
    
    CGFloat length = 0;
    for (int i=0; i<self.layoutData.count; i++) {
        length += [self lengthForSectionAtIndex:i];
    }
    
    return contentSize;
}

// UICollectionView calls these four methods to determine the layout information.
// Implement -layoutAttributesForElementsInRect: to return layout attributes for supplementary or decoration views, or to perform layout in an as-needed-on-screen fashion.
// Additionally, all layout subclasses should implement -layoutAttributesForItemAtIndexPath: to return layout attributes instances on demand for specific index paths.
// If the layout supports any supplementary or decoration view types, it should also implement the respective atIndexPath: methods for those types.

// return an array layout attributes instances for all the views in the given rect
- (NSArray *)layoutAttributesForElementsInRect:(CGRect)rect
{
#warning incomplete
    return @[];
}
- (UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath
{
    SWCollectionViewLineLayoutAttributes *attributes = (SWCollectionViewLineLayoutAttributes *)[super layoutAttributesForItemAtIndexPath:indexPath];
    
    // TODO compute side in case data source doesn't specify it
    [attributes setSide:SWCollectionViewLineLayoutAttributeSideLeft];
    
    if ([self.collectionView.dataSource conformsToProtocol:@protocol(SWCollectionViewDataSourceLineLayout)] &&
        [self.collectionView.dataSource respondsToSelector:@selector(sideForItemAtIndexPath:)]) {
        [attributes setSide:[((id<SWCollectionViewDataSourceLineLayout>)self.collectionView.dataSource) sideForItemAtIndexPath:indexPath]];
    }
    return attributes;
}
- (UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryViewOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath
{
#warning incomplete
    return [super layoutAttributesForSupplementaryViewOfKind:kind atIndexPath:indexPath];
}
- (UICollectionViewLayoutAttributes *)layoutAttributesForDecorationViewOfKind:(NSString*)decorationViewKind atIndexPath:(NSIndexPath *)indexPath
{
#warning incomplete
    return [super layoutAttributesForDecorationViewOfKind:decorationViewKind atIndexPath:indexPath];
}

//- (BOOL)shouldInvalidateLayoutForBoundsChange:(CGRect)newBounds; // return YES to cause the collection view to requery the layout for geometry information
//- (CGPoint)targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset withScrollingVelocity:(CGPoint)velocity; // return a point at which to rest after scrolling - for layouts that want snap-to-point scrolling behavior

#pragma mark - Private Helpers

- (CGFloat)lengthForSectionAtIndex:(NSInteger)index
{
    NSDictionary *section = [self.layoutData objectAtIndex:index];
    CGFloat length = ((NSNumber *)[section objectForKey:@"headerLength"]).floatValue +
    ((NSNumber *)[section objectForKey:@"footerLength"]).floatValue +
    ((NSNumber *)[section objectForKey:@"insetLeading"]).floatValue +
    ((NSNumber *)[section objectForKey:@"insetTrailing"]).floatValue;
    
    /* TODO more math
     *
     */
    
    return length;
}

@end
