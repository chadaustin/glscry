#ifndef BOOST_GRAPH_DETAIL_CONTAINER_TRAITS_H
#define BOOST_GRAPH_DETAIL_CONTAINER_TRAITS_H

// Sure would be nice to be able to forward declare these
// instead of pulling in all the headers. Too bad that
// is not legal. There ought to be a standard <stlfwd> header. -JGS 

#include <boost/next_prior.hpp>

#include <algorithm>   // for std::remove
#include <vector>
#include <list>
#include <map>
#include <set>
#ifndef BOOST_NO_SLIST
#  include <slist>
#endif
#ifndef BOOST_NO_HASH
#  include <hash_map>
#  include <hash_set>
#endif

// The content of this file is in 'graph_detail' because otherwise
// there will be name clashes with 
// sandbox/boost/sequence_algo/container_traits.hpp
// The 'detail' subnamespace will still cause problems.
namespace boost { namespace graph_detail {

  //======================================================================
  // Container Category Tags
  //
  //   They use virtual inheritance because there are lots of
  //   inheritance diamonds.

  struct container_tag { };
  struct forward_container_tag : virtual public container_tag { };
  struct reversible_container_tag : virtual public forward_container_tag { };
  struct random_access_container_tag
    : virtual public reversible_container_tag { };
  
  struct sequence_tag : virtual public forward_container_tag { };

  struct associative_container_tag : virtual public forward_container_tag { };

  struct sorted_associative_container_tag 
    : virtual public associative_container_tag,
      virtual public reversible_container_tag { };

  struct front_insertion_sequence_tag : virtual public sequence_tag { };
  struct back_insertion_sequence_tag : virtual public sequence_tag { };

  struct unique_associative_container_tag 
    : virtual public associative_container_tag { };
  struct multiple_associative_container_tag 
    : virtual public associative_container_tag { };
  struct simple_associative_container_tag 
    : virtual public associative_container_tag { };
  struct pair_associative_container_tag 
    : virtual public associative_container_tag { };


  //======================================================================
  // Iterator Stability Tags
  //
  // Do mutating operations such as insert/erase/resize invalidate all
  // outstanding iterators?

  struct stable_tag { };
  struct unstable_tag { };

  //======================================================================
  // Container Traits Class and container_category() function

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  // don't use this unless there is partial specialization 
  template <class Container>
  struct container_traits {
    typedef typename Container::category category;
    typedef typename Container::iterator_stability iterator_stability;
  };
#endif

  // Use this as a compile-time assertion that X is stable
  inline void require_stable(stable_tag) { }

  // std::vector
  struct vector_tag :
    virtual public random_access_container_tag,
    virtual public back_insertion_sequence_tag { };

  template <class T, class Alloc>
  vector_tag container_category(const std::vector<T,Alloc>&)
    { return vector_tag(); }

  template <class T, class Alloc>
  unstable_tag iterator_stability(const std::vector<T,Alloc>&)
    { return unstable_tag(); }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class T, class Alloc>
  struct container_traits< std::vector<T,Alloc> > {
    typedef vector_tag category;
    typedef unstable_tag iterator_stability;
  };
#endif

  // std::list
  struct list_tag :
    virtual public reversible_container_tag,
    virtual public back_insertion_sequence_tag
    // this causes problems for push_dispatch...
    //    virtual public front_insertion_sequence_tag
    { };

  template <class T, class Alloc>
  list_tag container_category(const std::list<T,Alloc>&)
    { return list_tag(); }

  template <class T, class Alloc>
  stable_tag iterator_stability(const std::list<T,Alloc>&)
    { return stable_tag(); }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class T, class Alloc>
  struct container_traits< std::list<T,Alloc> > {
    typedef list_tag category;
    typedef stable_tag iterator_stability;
  };
#endif


  // std::slist
#ifndef BOOST_NO_SLIST
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class T, class Alloc>
  struct container_traits<BOOST_STD_EXTENSION_NAMESPACE::slist<T,Alloc> > {
    typedef front_insertion_sequence_tag category;
    typedef stable_tag iterator_stability;
  };
#endif
  template <class T, class Alloc>
  front_insertion_sequence_tag container_category(
  const BOOST_STD_EXTENSION_NAMESPACE::slist<T,Alloc>&
  )
    { return front_insertion_sequence_tag(); }

  template <class T, class Alloc>
  stable_tag iterator_stability(
  const BOOST_STD_EXTENSION_NAMESPACE::slist<T,Alloc>&)
    { return stable_tag(); }
#endif


  // std::set
  struct set_tag :
    virtual public sorted_associative_container_tag,
    virtual public simple_associative_container_tag,
    virtual public unique_associative_container_tag 
    { };

  template <class Key, class Cmp, class Alloc> 
  set_tag container_category(const std::set<Key,Cmp,Alloc>&)
  { return set_tag(); }

  template <class Key, class Cmp, class Alloc> 
  stable_tag iterator_stability(const std::set<Key,Cmp,Alloc>&)
  { return stable_tag(); }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class Key, class Cmp, class Alloc> 
  struct container_traits< std::set<Key,Cmp,Alloc> > {
    typedef set_tag category;
    typedef stable_tag iterator_stability;
  };
#endif

  // std::multiset
  struct multiset_tag :
    virtual public sorted_associative_container_tag,
    virtual public simple_associative_container_tag,
    virtual public multiple_associative_container_tag 
    { };

  template <class Key, class Cmp, class Alloc> 
  multiset_tag container_category(const std::multiset<Key,Cmp,Alloc>&)
  { return multiset_tag(); }

  template <class Key, class Cmp, class Alloc> 
  stable_tag iterator_stability(const std::multiset<Key,Cmp,Alloc>&)
  { return stable_tag(); }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class Key, class Cmp, class Alloc> 
  struct container_traits< std::multiset<Key,Cmp,Alloc> > {
    typedef multiset_tag category;
    typedef stable_tag iterator_stability;
  };
#endif

  // deque

  // std::map
  struct map_tag :
    virtual public sorted_associative_container_tag,
    virtual public pair_associative_container_tag,
    virtual public unique_associative_container_tag 
    { };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class Key, class T, class Cmp, class Alloc> 
  struct container_traits< std::map<Key,T,Cmp,Alloc> > {
    typedef map_tag category;
    typedef stable_tag iterator_stability;
  };
#endif

  template <class Key, class T, class Cmp, class Alloc> 
  map_tag container_category(const std::map<Key,T,Cmp,Alloc>&)
  { return map_tag(); }

  template <class Key, class T, class Cmp, class Alloc> 
  stable_tag iterator_stability(const std::map<Key,T,Cmp,Alloc>&)
  { return stable_tag(); }

  // std::multimap
  struct multimap_tag :
    virtual public sorted_associative_container_tag,
    virtual public pair_associative_container_tag,
    virtual public multiple_associative_container_tag 
    { };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class Key, class T, class Cmp, class Alloc> 
  struct container_traits< std::multimap<Key,T,Cmp,Alloc> > {
    typedef multimap_tag category;
    typedef stable_tag iterator_stability;
  };
#endif

  template <class Key, class T, class Cmp, class Alloc> 
  multimap_tag container_category(const std::multimap<Key,T,Cmp,Alloc>&)
  { return multimap_tag(); }

  template <class Key, class T, class Cmp, class Alloc> 
  stable_tag iterator_stability(const std::multimap<Key,T,Cmp,Alloc>&)
  { return stable_tag(); }


 // hash_set, hash_map

#ifndef BOOST_NO_HASH
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class Key, class Eq, class Hash, class Alloc> 
  struct container_traits< BOOST_STD_EXTENSION_NAMESPACE::hash_set<Key,Eq,Hash,Alloc> > {
    typedef set_tag category;
    typedef stable_tag iterator_stability; // is this right?
  };
  template <class Key, class T, class Eq, class Hash, class Alloc>
  struct container_traits< BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key,T,Eq,Hash,Alloc> > {
    typedef map_tag category;
    typedef stable_tag iterator_stability; // is this right?
  };
#endif
  template <class Key, class Eq, class Hash, class Alloc>
  set_tag container_category(const BOOST_STD_EXTENSION_NAMESPACE::hash_set<Key,Eq,Hash,Alloc>&)
  { return set_tag(); }

  template <class Key, class T, class Eq, class Hash, class Alloc>
  map_tag container_category(const BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key,T,Eq,Hash,Alloc>&)
  { return map_tag(); }

  template <class Key, class Eq, class Hash, class Alloc>
  stable_tag iterator_stability(const BOOST_STD_EXTENSION_NAMESPACE::hash_set<Key,Eq,Hash,Alloc>&)
  { return stable_tag(); }

  template <class Key, class T, class Eq, class Hash, class Alloc>
  stable_tag iterator_stability(const BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key,T,Eq,Hash,Alloc>&)
  { return stable_tag(); }
#endif



  //===========================================================================
  // Generalized Container Functions


  // Erase
  template <class Sequence, class T>
  void erase_dispatch(Sequence& c, const T& x, 
                      sequence_tag)
  {
    c.erase(std::remove(c.begin(), c.end(), x), c.end());
  }

  template <class AssociativeContainer, class T>
  void erase_dispatch(AssociativeContainer& c, const T& x, 
                      associative_container_tag)
  {
    c.erase(x);
  }
  template <class Container, class T>
  void erase(Container& c, const T& x)
  {
    erase_dispatch(c, x, container_category(c));
  }

  // Erase If
  template <class Sequence, class Predicate, class IteratorStability>
  void erase_if_dispatch(Sequence& c, Predicate p,
                         sequence_tag, IteratorStability)
  {
#if 0
    c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
#else
    if (! c.empty())
      c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
#endif
  }
  template <class AssociativeContainer, class Predicate>
  void erase_if_dispatch(AssociativeContainer& c, Predicate p,
                         associative_container_tag, stable_tag)
  {
    typename AssociativeContainer::iterator i, next;
    for (i = next = c.begin(); next != c.end(); i = next) {
      ++next;
      if (p(*i))
        c.erase(i);
    }
  }
  template <class AssociativeContainer, class Predicate>
  void erase_if_dispatch(AssociativeContainer& c, Predicate p,
                         associative_container_tag, unstable_tag)
  {
    // This method is really slow, so hopefully we won't have any
    // associative containers with unstable iterators!
    // Is there a better way to do this?
    typename AssociativeContainer::iterator i;
    typename AssociativeContainer::size_type n = c.size();
    while (n--)
      for (i = c.begin(); i != c.end(); ++i)
        if (p(*i)) {
          c.erase(i);
          break;
        }
  }
  template <class Container, class Predicate>
  void erase_if(Container& c, Predicate p)
  {
    erase_if_dispatch(c, p, container_category(c), iterator_stability(c));
  }

  // Push
  template <class Container, class T>
  std::pair<typename Container::iterator, bool>
  push_dispatch(Container& c, const T& v, back_insertion_sequence_tag)
  {
    c.push_back(v);
    return std::make_pair(boost::prior(c.end()), true);
  }

  template <class Container, class T>
  std::pair<typename Container::iterator, bool>
  push_dispatch(Container& c, const T& v, front_insertion_sequence_tag)
  {
    c.push_front(v);
    return std::make_pair(c.begin(), true);
  }

  template <class AssociativeContainer, class T>
  std::pair<typename AssociativeContainer::iterator, bool>
  push_dispatch(AssociativeContainer& c, const T& v, 
                unique_associative_container_tag)
  {
    return c.insert(v);
  }

  template <class AssociativeContainer, class T>
  std::pair<typename AssociativeContainer::iterator, bool>
  push_dispatch(AssociativeContainer& c, const T& v,
                multiple_associative_container_tag)
  {
    return std::make_pair(c.insert(v), true);
  }

  template <class Container, class T>
  std::pair<typename Container::iterator,bool>
  push(Container& c, const T& v)
  {
    return push_dispatch(c, v, container_category(c));
  }

}} // namespace boost::graph_detail

#endif // BOOST_GRAPH_DETAIL_CONTAINER_TRAITS_H
