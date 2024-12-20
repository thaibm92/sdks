//
//  SHMediaLibrary.h
//  ShazamKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHMediaItem.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @brief @c SHMediaLibrary represents the user's synced Shazam library.
/// @discussion You can add new @c SHMediaItem instances to the user's library.
SH_EXPORT API_DEPRECATED("Use SHLibrary instead", macos(12.0, 15.0), ios(15.0, 18.0), tvos(15.0, 18.0), watchos(8.0, 11.0))
@interface SHMediaLibrary : NSObject

/// @brief Returns an instance of the default Shazam library.
@property (class, NS_NONATOMIC_IOSONLY, strong, readonly) SHMediaLibrary *defaultLibrary;

/// Adds an array of media items to the user's Shazam library.
///
/// @discussion For each @c SHMediaItem instance passed in, the following @c SHMediaItemProperty keys will be saved:
/// @c SHMediaItemShazamID, @c SHMediaItemTitle, @c SHMediaItemSubtitle.
/// If @c SHMediaItemSubtitle is not set it may fallback to use @c SHMediaItemArtist if available.
///
/// @note @c SHMediaItemShazamID is required for each @c SHMediaItem to be considered valid.
/// @c SHMediaItemShazamID must be a numeric only string
///
/// @param mediaItems An array containing the @c SHMediaItem objects to be added to the library.
/// @param completionHandler A block called after all valid @c SHMediaItem objects have been added to the library. If an error occurred, the error parameter will be populated.
- (void)addMediaItems:(NSArray<SHMediaItem *> *)mediaItems completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * __nullable error))completionHandler;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
