/*
 *                         Vortex Lite
 *
 *   This software and documentation are Copyright 2006 to 2015 PrismTech
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $LITE_HOME/LICENSE
 *
 *   for full copyright notice and license terms.
 *
 */
#ifndef OMG_DDS_SUB_DETAIL_TANYDATAREADER_HPP_
#define OMG_DDS_SUB_DETAIL_TANYDATAREADER_HPP_

/**
 * @file
 */

/*
 * OMG PSM class declaration
 */

#include <dds/sub/TAnyDataReader.hpp>
#include <dds/topic/TopicDescription.hpp>

// Implementation

namespace dds
{
namespace sub
{

template <typename DELEGATE>
TAnyDataReader<DELEGATE>::~TAnyDataReader() {}

template <typename DELEGATE>
const dds::sub::Subscriber&
TAnyDataReader<DELEGATE>::subscriber() const
{
    return this->delegate()->subscriber();
}

template <typename DELEGATE>
const dds::topic::TopicDescription&
TAnyDataReader<DELEGATE>::topic_description() const
{
    return this->delegate()->topic_description();
}

template <typename DELEGATE>
void
TAnyDataReader<DELEGATE>::wait_for_historical_data(const dds::core::Duration& timeout)
{
    this->delegate()->wait_for_historical_data(timeout);
}


template <typename DELEGATE>
dds::sub::qos::DataReaderQos
TAnyDataReader<DELEGATE>::qos() const
{
    return this->delegate()->qos();
}

template <typename DELEGATE>
void
TAnyDataReader<DELEGATE>::qos(const dds::sub::qos::DataReaderQos& qos)
{
    this->delegate()->qos(qos);
}

template <typename DELEGATE>
TAnyDataReader<DELEGATE>&
TAnyDataReader<DELEGATE>::operator << (const dds::sub::qos::DataReaderQos& qos)
{
    this->delegate()->qos(qos);
    return *this;
}

template <typename DELEGATE>
const TAnyDataReader<DELEGATE>&
TAnyDataReader<DELEGATE>::operator >> (dds::sub::qos::DataReaderQos& qos) const
{
    qos = this->delegate()->qos();
    return *this;
}


template <typename DELEGATE>
dds::core::status::LivelinessChangedStatus
TAnyDataReader<DELEGATE>::liveliness_changed_status()
{
    return this->delegate()->liveliness_changed_status();
}

template <typename DELEGATE>
dds::core::status::SampleRejectedStatus
TAnyDataReader<DELEGATE>::sample_rejected_status()
{
    return this->delegate()->sample_rejected_status();
}

template <typename DELEGATE>
dds::core::status::SampleLostStatus
TAnyDataReader<DELEGATE>::sample_lost_status()
{
    return this->delegate()->sample_lost_status();
}

template <typename DELEGATE>
dds::core::status::RequestedDeadlineMissedStatus
TAnyDataReader<DELEGATE>::requested_deadline_missed_status()
{
    return this->delegate()->requested_deadline_missed_status();
}

template <typename DELEGATE>
dds::core::status::RequestedIncompatibleQosStatus
TAnyDataReader<DELEGATE>::requested_incompatible_qos_status()
{
    return this->delegate()->requested_incompatible_qos_status();
}

template <typename DELEGATE>
dds::core::status::SubscriptionMatchedStatus
TAnyDataReader<DELEGATE>::subscription_matched_status()
{
    return this->delegate()->subscription_matched_status();
}

}
}
// End of implementation

#endif /* OMG_DDS_SUB_DETAIL_TANYDATAREADER_HPP_ */
