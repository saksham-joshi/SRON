
#ifndef _STACK_SET_H_
#define _STACK_SET_H_

#include "_seek_tracker_.hpp"

class VariableIndexer 
{
    std::vector < std::set < struct IndexAndHash > > _stack;
    using VariableHash_t   = decltype(IndexAndHash::_hash);
    using VariableIndex_t  = decltype(IndexAndHash::_index);
    VariableIndex_t _index;

    public : 

        constexpr static const VariableIndex_t MAX_INDEX = 65535;


        inline VariableIndexer ( ) { this->_index = 0; }


        inline VariableIndex_t insert ( const SronHasher& __obj )
        {
            if ( this->_stack.empty() )
            {
                throw ThrowException("inserting new variable to stack. The stack is empty and a new variable cannot be inserted without existence of unit set", SronError::CompilerError);
            }
            
            else if ( this->_index == VariableIndexer::MAX_INDEX )
            {
                throw ThrowException("inserting a new variable to stack. Too many variables are declared which crossed the limit");
            }

            this->_stack.back().insert( IndexAndHash( __obj.GET() , this->_index) );

            return this->_index++;

        }


        inline VariableIndex_t bfs( VariableHash_t __hash ) const noexcept
        {
            if ( ! this->_stack.empty() )
            {
                auto revit = this->_stack.end() - 1;
                const auto start = this->_stack.begin();

                while ( revit >= start )
                {
                    auto variable_found = revit->find( __hash );
                    
                    if ( variable_found != revit->end() ) return variable_found->_index;

                    --revit;
                }
            }

            return VariableIndexer::MAX_INDEX;
        }

        inline VariableIndex_t find( const SronHasher& __obj )
        {
            return this->bfs( __obj.GET() );
        }

        inline VariableIndex_t end ( ) const noexcept
        {
            return this->MAX_INDEX;
        }

        inline void clear() noexcept 
        {
            this->_stack.clear();
            this->_index = 0;
        }

        inline void addLayer() 
        {
            this->_stack.emplace_back();
        }

        inline void popLayer()
        {
            if ( this->_stack.empty() )
            {
                throw ThrowException("popping the top layer of stack. The stack is empty and a layer cannot popped", SronError::CompilerError);
            }

            this->_stack.pop_back();
        }

        inline VariableIndex_t totalVariables() const noexcept 
        {
            return this->_index;
        }
};

#endif