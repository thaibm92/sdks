//
//  MPSScatterNDOps.h
//  MPSGraph
//
//  Created on 3/6/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSScatterNDOps_h
#define MPSScatterNDOps_h

NS_ASSUME_NONNULL_BEGIN

/// The scatter mode.
typedef NS_ENUM(NSInteger, MPSGraphScatterMode)
{
    /// Add
    MPSGraphScatterModeAdd     MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(add) =  0L,
    /// Sub
    MPSGraphScatterModeSub     MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                     =  1L,
    /// Multiply
    MPSGraphScatterModeMul     MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                     =  2L,
    /// Divide
    MPSGraphScatterModeDiv     MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                     =  3L,
    /// Minimum
    MPSGraphScatterModeMin     MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                     =  4L,
    /// Maximum
    MPSGraphScatterModeMax     MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                     =  5L,
    /// Set
    MPSGraphScatterModeSet     MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                     =  6L,
};

#pragma mark ScatterND

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(ScatterNDOps)

/// Creates a ScatterND operation and returns the result tensor.
///
/// Scatters the slices in updatesTensor to the result tensor along the indices in indicesTensor. 
/// The scatter is defined as 
/// ```md 
/// B = batchDims 
/// U = updates.rank - B 
/// P = res.rank - B 
/// Q = inds.rank - B 
/// K = inds.shape[-1] 
/// index_slice = indices[i_{b0},...,i_{bB},i_{0},..,i_{Q-1}] 
/// res[i_{b0},...,i_{bB},index_slice[0],...,index_slice[K-1]] = updates[i_{b0},...,i_{bB},i_{0},...,i_{Q-1}] 
/// ``` 
/// Collisions will be summed, and slices not set by indices are set to 0. The tensors have the following shape requirements
/// ```md 
/// K <= P 
/// U = (P-K) + Q-1 
/// indices.shape[0:Q-1] = updates.shape[0:Q-1] 
/// updates.shape[Q:U] = res.shape[K:P] 
/// ```
///
/// - Parameters:
///   - updatesTensor: Tensor containing slices to be inserted into the result tensor.
///   - indicesTensor: Tensor containg the result indices to insert slices at
///   - shape: The shape of the result tensor.
///   - batchDimensions: The number of batch dimensions
///   - mode: The type of update to use on the destination
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) scatterNDWithUpdatesTensor:(MPSGraphTensor *) updatesTensor
                                  indicesTensor:(MPSGraphTensor *) indicesTensor
                                          shape:(MPSShape *) shape
                                batchDimensions:(NSUInteger) batchDimensions
                                           mode:(MPSGraphScatterMode) mode
                                           name:(NSString * _Nullable) name;

/// Creates a ScatterND operation and returns the result tensor.
///
/// Scatters the slices in updatesTensor to the result tensor along the indices in indicesTensor. 
/// The scatter is defined as 
/// ```md 
/// B = batchDims 
/// U = updates.rank - B 
/// P = res.rank - B 
/// Q = inds.rank - B 
/// K = inds.shape[-1] 
/// index_slice = indices[i_{b0},...,i_{bB},i_{0},..,i_{Q-1}] 
/// res[i_{b0},...,i_{bB},index_slice[0],...,index_slice[K-1]] = updates[i_{b0},...,i_{bB},i_{0},...,i_{Q-1}] 
/// ``` 
/// Collisions will be summed, and slices not set by indices are set to 0. The tensors have the following shape requirements
/// ```md 
/// K <= P 
/// U = (P-K) + Q-1 
/// indices.shape[0:Q-1] = updates.shape[0:Q-1] 
/// updates.shape[Q:U] = res.shape[K:P] 
/// ```
///
/// - Parameters:
///   - updatesTensor: Tensor containing slices to be inserted into the result tensor.
///   - indicesTensor: Tensor containg the result indices to insert slices at
///   - shape: The shape of the result tensor.
///   - batchDimensions: The number of batch dimensions
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) scatterNDWithUpdatesTensor:(MPSGraphTensor *) updatesTensor
                                  indicesTensor:(MPSGraphTensor *) indicesTensor
                                          shape:(MPSShape *) shape
                                batchDimensions:(NSUInteger) batchDimensions
                                           name:(NSString * _Nullable) name;

/// Creates a ScatterND operation and returns the result tensor.
///
/// Scatters the slices in updatesTensor to the result tensor along the indices in indicesTensor, on top of dataTensor. 
/// The scatter is defined as 
/// ```md 
/// B = batchDims 
/// U = updates.rank - B 
/// P = res.rank - B 
/// Q = inds.rank - B 
/// K = inds.shape[-1] 
/// index_slice = indices[i_{b0},...,i_{bB},i_{0},..,i_{Q-1}] 
/// res[...] = data[...] 
/// res[i_{b0},...,i_{bB},index_slice[0],...,index_slice[K-1]] += updates[i_{b0},...,i_{bB},i_{0},...,i_{Q-1}] // Note += is used but this depends on mode 
/// ``` 
/// Collisions will be updated according to mode, and slices not set by indices are set to 0. The tensors have the following shape requirements
/// ```md 
/// K <= P 
/// U = (P-K) + Q-1 
/// data.shape = res.shape 
/// indices.shape[0:Q-1] = updates.shape[0:Q-1] 
/// updates.shape[Q:U] = res.shape[K:P] 
/// ```
///
/// - Parameters:
///   - dataTensor: Tensor containing inital values of same shape as result tensor
///   - updatesTensor: Tensor containing slices to be inserted into the result tensor.
///   - indicesTensor: Tensor containg the result indices to insert slices at
///   - batchDimensions: The number of batch dimensions
///   - mode: The type of update to use on the destination
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) scatterNDWithDataTensor:(MPSGraphTensor *) dataTensor
                               updatesTensor:(MPSGraphTensor *) updatesTensor
                               indicesTensor:(MPSGraphTensor *) indicesTensor
                             batchDimensions:(NSUInteger) batchDimensions
                                        mode:(MPSGraphScatterMode) mode
                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( scatterNDWithData(_:updates:indices:batchDimensions:mode:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

@end

#pragma mark Scatter

@interface MPSGraph(MPSGraphScatterOps)

/// Creates a Scatter operation and returns the result tensor.
///
/// Scatters the slices in updatesTensor to the result tensor along the indices in indicesTensor. 
/// The scatter is defined as 
/// ```md 
/// U = updates.rank 
/// P = res.rank 
/// res[i_{0},...,i_{axis-1},indices[i_{axis}],i_{axis+1},...,i_{U-1}] = updates[i_{0},...,i_{axis-1},i_{axis},i_{axis+1},...,i_{U-1}] 
/// ``` 
/// Collisions will be updated according to mode. The tensors have the following shape requirements
/// ```md 
/// U = P 
/// indices.rank = 1 
/// updates.shape[0:axis-1] = res.shape[0:axis-1] 
/// updates.shape[axis] = indices.shape[0] 
/// updates.shape[axis+1:U] = res.shape[0:P] 
/// ```
///
/// - Parameters:
///   - updatesTensor: Tensor containing values to be inserted into the result tensor.
///   - indicesTensor: Tensor containg the result indices to insert values at.
///   - shape: The shape of the result tensor.
///   - axis: The axis of the result tensor to scatter values along.
///   - mode: The type of update to use on the destination.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) scatterWithUpdatesTensor:(MPSGraphTensor *) updatesTensor
                                indicesTensor:(MPSGraphTensor *) indicesTensor
                                        shape:(MPSShape *) shape
                                         axis:(NSInteger) axis
                                         mode:(MPSGraphScatterMode) mode
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( scatter(_:indices:shape:axis:mode:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Creates a Scatter operation and returns the result tensor.
///
/// Scatters the slices in updatesTensor to the result tensor along the indices in indicesTensor, on top of dataTensor. 
/// The scatter is defined as 
/// ```md 
/// U = updates.rank 
/// P = res.rank 
/// res[...] = data[...] 
/// res[i_{0},...,i_{axis-1},indices[i_{axis}],i_{axis+1},...,i_{U-1}] += updates[i_{0},...,i_{axis-1},i_{axis},i_{axis+1},...,i_{U-1}] // Note += is used but this depends on mode 
/// ``` 
/// Collisions will be updated according to mode. The tensors have the following shape requirements
/// ```md 
/// U = P 
/// indices.rank = 1 
/// data.shape = res.shape 
/// updates.shape[0:axis-1] = res.shape[0:axis-1] 
/// updates.shape[axis] = indices.shape[0] 
/// updates.shape[axis+1:U] = res.shape[0:P] 
/// ```
///
/// - Parameters:
///   - dataTensor: Tensor containing inital values of same shape as result tensor
///   - updatesTensor: Tensor containing values to be inserted into the result tensor.
///   - indicesTensor: Tensor containg the result indices to insert values at
///   - axis: The axis of the result tensor to scatter values along
///   - mode: The type of update to use on the destination
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) scatterWithDataTensor:(MPSGraphTensor *) dataTensor
                             updatesTensor:(MPSGraphTensor *) updatesTensor
                             indicesTensor:(MPSGraphTensor *) indicesTensor
                                      axis:(NSInteger) axis
                                      mode:(MPSGraphScatterMode) mode
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( scatterWithData(_:updates:indices:axis:mode:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));
@end

@interface MPSGraph(MPSGraphScatterAlongAxisOps)

/// Creates a ScatterAlongAxis operation and returns the result tensor.
///
/// Scatter values from `updatesTensor` along the specified `axis` at indices in `indicesTensor` into a result tensor. 
/// Values are updated following `mode`. See MPSGraphScatterMode. 
/// The shape of `updatesTensor` and `indicesTensor` must match. `shape` must match except at `axis`. 
/// The shape of the result tensor is equal to `shape` and initialized with an initial value corresponding to `mode`. 
/// If an index is out of bounds of `shape` along `axis` the update value is skipped.
///
/// - Parameters:
///   - axis: The axis to scatter to. Negative values wrap around
///   - updatesTensor: The input tensor to scatter values from
///   - indicesTensor: Int32 or Int64 tensor used to index the result tensor.
///   - mode: The type of update to use
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) scatterAlongAxis:(NSInteger) axis
                    withUpdatesTensor:(MPSGraphTensor *) updatesTensor
                        indicesTensor:(MPSGraphTensor *) indicesTensor
                                shape:(MPSShape *) shape
                                 mode:(MPSGraphScatterMode) mode
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( scatterAlongAxis(_:updates:indices:shape:mode:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a ScatterAlongAxis operation and returns the result tensor.
///
/// Scatter values from `updatesTensor` along the specified `axis` at indices in `indicesTensor` into a result tensor.
/// Values are updated following `mode`. See MPSGraphScatterMode.
/// The shape of `updatesTensor` and `indicesTensor` must match. `shape` must match except at `axis`.
/// The shape of the result tensor is equal to `shape` and initialized with an initial value corresponding to `mode`.
/// If an index is out of bounds of `shape` along `axis` the update value is skipped.
///
/// - Parameters:
///   - axisTensor: Scalar Int32 tensor. The axis to scatter to. Negative values wrap around
///   - updatesTensor: The input tensor to scatter values from
///   - indicesTensor: Int32 or Int64 tensor used to index the result tensor.
///   - mode: The type of update to use
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) scatterAlongAxisTensor:(MPSGraphTensor *) axisTensor
                          withUpdatesTensor:(MPSGraphTensor *) updatesTensor
                              indicesTensor:(MPSGraphTensor *) indicesTensor
                                      shape:(MPSShape *) shape
                                       mode:(MPSGraphScatterMode) mode
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( scatterAlongAxisTensor(_:updates:indices:shape:mode:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a ScatterAlongAxis operation and returns the result tensor.
///
/// Scatter values from `updatesTensor` along the specified `axis` at indices in `indicesTensor` onto `dataTensor`. 
/// Values in `dataTensor` are updated following `mode`. See MPSGraphScatterMode. 
/// The shape of `updatesTensor` and `indicesTensor` must match. The shape of `dataTensor` must match except at `axis`. 
/// If an index is out of bounds of `shape` along `axis` the update value is skipped. 
/// For example, 
/// ```md
/// data = [ [0, 0, 0],
///          [1, 1, 1],
///          [2, 2, 2],
///          [3, 3, 3] ]
/// updates = [ [1, 2, 3],
///             [4, 5, 6] ]
/// indices = [ [2, 1, 0],
///             [1, 3, 2] ]
/// axis = 0
/// result = scatterAlongAxis(axis, data, updates, indices, MPSGraphScatterModeAdd, "scatter")
/// result = [ [0, 0, 3],
///            [5, 3, 1],
///            [3, 2, 8],
///            [3, 8, 3] ]
/// ```
///
/// - Parameters:
///   - axis: The axis to scatter to. Negative values wrap around
///   - dataTensor: The input tensor to scatter values onto
///   - updatesTensor: The input tensor to scatter values from
///   - indicesTensor: Int32 or Int64 tensor used to index the result tensor.
///   - mode: The type of update to use
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) scatterAlongAxis:(NSInteger) axis
                       withDataTensor:(MPSGraphTensor *) dataTensor
                        updatesTensor:(MPSGraphTensor *) updatesTensor
                        indicesTensor:(MPSGraphTensor *) indicesTensor
                                 mode:(MPSGraphScatterMode) mode
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( scatterAlongAxis(_:data:updates:indices:mode:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Creates a ScatterAlongAxis operation and returns the result tensor.
///
/// Scatter values from `updatesTensor` along the specified `axis` at indices in `indicesTensor` onto `dataTensor`.
/// Values in `dataTensor` are updated following `mode`. See MPSGraphScatterMode.
/// The shape of `updatesTensor` and `indicesTensor` must match. The shape of `dataTensor` must match except at `axis`.
/// If an index is out of bounds of `shape` along `axis` the update value is skipped.
/// For example,
/// ```md
/// data = [ [0, 0, 0],
///          [1, 1, 1],
///          [2, 2, 2],
///          [3, 3, 3] ]
/// updates = [ [1, 2, 3],
///             [4, 5, 6] ]
/// indices = [ [2, 1, 0],
///             [1, 3, 2] ]
/// axis = 0
/// result = scatterAlongAxis(axis, data, updates, indices, MPSGraphScatterModeAdd, "scatter")
/// result = [ [0, 0, 3],
///            [5, 3, 1],
///            [3, 2, 8],
///            [3, 8, 3] ]
/// ```
///
/// - Parameters:
///   - axisTensor: Scalar Int32 tensor. The axis to scatter to. Negative values wrap around
///   - dataTensor: The input tensor to scatter values onto
///   - updatesTensor: The input tensor to scatter values from
///   - indicesTensor: Int32 or Int64 tensor used to index the result tensor.
///   - mode: The type of update to use
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
- (MPSGraphTensor *) scatterAlongAxisTensor:(MPSGraphTensor *) axisTensor
                             withDataTensor:(MPSGraphTensor *) dataTensor
                              updatesTensor:(MPSGraphTensor *) updatesTensor
                              indicesTensor:(MPSGraphTensor *) indicesTensor
                                       mode:(MPSGraphScatterMode) mode
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( scatterAlongAxisTensor(_:data:updates:indices:mode:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSScatterNDOps_h */
