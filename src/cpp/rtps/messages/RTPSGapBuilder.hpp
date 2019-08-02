// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file RTPSGapBuilder.h
 *
 */

#ifndef RTPSGAPBUILDER_H_
#define RTPSGAPBUILDER_H_
#ifndef DOXYGEN_SHOULD_SKIP_THIS_PUBLIC

#include <fastrtps/rtps/messages/RTPSMessageGroup.h>

namespace eprosima {
namespace fastrtps {
namespace rtps {

/**
 * A helper class to add GAP messages to a @ref RTPSMessageGroup.
 * @ingroup WRITER_MODULE
 */
class RTPSGapBuilder
{
public:

    /**
     * RTPSGapBuilder constructor.
     *
     * @param group Referemce to the @ref RTPSMessageGroup that will be used to send GAP messages.
     */
    explicit RTPSGapBuilder(
            RTPSMessageGroup& group)
        : group_(group)
    {
    }

    ~RTPSGapBuilder();

    /**
     * Adds a sequence number to the GAP list.
     *
     * @remark Sequence numbers should be added in strict increasing order.
     * 
     * @param gap_sequence Sequence number to be added to the GAP list.
     * @return false if a GAP message couldn't be added to the message group,
     *         true if no GAP message was needed or it was successfully added.
     *
     * @throws RTPSMessageGroup::timeout if a network operation was necessary and
     *         it blocked for more than the maximum time allowed.
     */
    bool add(
            const SequenceNumber_t& gap_sequence);

    /**
     * Adds a GAP message to the message group if necessary.
     *
     * @return false if a GAP message couldn't be added to the message group,
     *         true if no GAP message was needed or it was successfully added.
     *
     * @throws RTPSMessageGroup::timeout if a network operation was necessary and
     *         it blocked for more than the maximum time allowed.
     */
    bool flush();

private:

    RTPSMessageGroup& group_;            ///< Reference to the message group used to output messages.
    bool is_gap_pending_ = false;        ///< Whether a GAP message is pending to be added.
    SequenceNumber_t initial_sequence_;  ///< Contiguous range initial sequence.
    SequenceNumberSet_t gap_bitmap_;     ///< Bitmap with non-contiguous sequences.
};

} /* namespace rtps */
} /* namespace fastrtps */
} /* namespace eprosima */

#endif
#endif /* RTPSGAPBUILDER_H_ */