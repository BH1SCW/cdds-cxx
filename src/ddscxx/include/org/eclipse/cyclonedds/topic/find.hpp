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


/**
 * @file
 */

#ifndef CYCLONEDDS_TOPIC_FIND_HPP_
#define CYCLONEDDS_TOPIC_FIND_HPP_

#include <dds/domain/DomainParticipant.hpp>
#include <dds/topic/TopicDescription.hpp>
#include <dds/topic/AnyTopic.hpp>
#include <dds/topic/Topic.hpp>
#include <dds/topic/ContentFilteredTopic.hpp>

namespace org
{
namespace eclipse
{
namespace cyclonedds
{
namespace topic
{

OMG_DDS_API dds::topic::TopicDescription
find_topic_description(
    const dds::domain::DomainParticipant& dp,
    const std::string& topic_name);

OMG_DDS_API dds::topic::AnyTopic
find_any_topic(
    const dds::domain::DomainParticipant& dp,
    const std::string& topic_name);


template <typename T, typename DELEGATE>
struct typed_finder {
    template <typename TOPIC>
    static inline TOPIC find(
            const dds::domain::DomainParticipant& dp,
            const std::string& topic_name);
};


template <typename T>
struct typed_finder<T, dds::topic::detail::ContentFilteredTopic<T> > {
    static inline dds::topic::ContentFilteredTopic<T> find(
            const dds::domain::DomainParticipant& dp,
            const std::string& topic_name)
    {
        dds::topic::ContentFilteredTopic<T> topic = dds::core::null;

        org::eclipse::cyclonedds::core::ObjectDelegate::ref_type entity = dp.delegate()->find_cfTopic(topic_name);

        if (entity) {
            typename dds::topic::ContentFilteredTopic<T>::DELEGATE_REF_T topic_typed =
                    OSPL_CXX11_STD_MODULE::dynamic_pointer_cast<typename dds::topic::ContentFilteredTopic<T>::DELEGATE_T>(entity);
            topic = dds::topic::ContentFilteredTopic<T>(topic_typed);
        }
        return topic;
    }
};

template <typename T>
struct typed_finder<T, dds::topic::detail::Topic<T> > {
    static inline dds::topic::Topic<T> find(
            const dds::domain::DomainParticipant& dp,
            const std::string& topic_name)
    {
        dds::topic::Topic<T> topic = dds::core::null;

        org::eclipse::cyclonedds::core::EntityDelegate::ref_type entity = dp.delegate()->find_topic(topic_name);

        if (entity) {
            typename dds::topic::Topic<T>::DELEGATE_REF_T topic_typed =
                    OSPL_CXX11_STD_MODULE::dynamic_pointer_cast<typename dds::topic::Topic<T>::DELEGATE_T>(entity);
            topic = dds::topic::Topic<T>(topic_typed);
        }
        return topic;
    }
};



template <typename TOPIC, typename DELEGATE>
struct finder {
    static inline TOPIC find(
            const dds::domain::DomainParticipant& dp,
            const std::string& topic_name)
    {
        return org::eclipse::cyclonedds::topic::typed_finder<typename TOPIC::DataType, typename TOPIC::DELEGATE_T>::find(dp, topic_name);
    }
};

template <>
struct finder<dds::topic::TopicDescription, org::eclipse::cyclonedds::topic::TopicDescriptionDelegate> {
    static inline dds::topic::TopicDescription find(
            const dds::domain::DomainParticipant& dp,
            const std::string& topic_name)
    {
         return find_topic_description(dp, topic_name);
    }
};

template <>
struct finder<dds::topic::AnyTopic, org::eclipse::cyclonedds::topic::AnyTopicDelegate> {
    static inline dds::topic::AnyTopic find(
            const dds::domain::DomainParticipant& dp,
            const std::string& topic_name)
    {
         return find_any_topic(dp, topic_name);
    }
};



}
}
}
}

#endif /* CYCLONEDDS_TOPIC_FIND_HPP_ */
