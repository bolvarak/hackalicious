<?hh


class VariantList extends Variant
{
	//////////////////////////////////////////////////////////////////////////////
	/// Properties //////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////


	/**
	 * This property contains the data for this map
	 * @access protected
	 * @name VariantList::$mData
	 * @var HH\Vector<Variant>
	 */
	protected Vector<Variant> $mData = Map {};

	//////////////////////////////////////////////////////////////////////////////
	/// Constructor /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method sets up the instance with existing data
	 * @access public
	 * @name VariantList::__construct()
	 * @param KeyedTraversable<Tk, Tv> $ktsSource [null]
	 * @return void
	 */
	public function __construct(?Traversable<Tv> $ktsSource = null) : Variant
	{
		// Check for data
		if (is_null($ktsSource) === false) {
			// Create a new map out of the
			$this->mData = new Vector($ktsSource);
			// Iterate over the map
			foreach ($this->mData->getIterator() as $intIndex => $mixValue) {
				// Reset the data
				$this->set($intIndex, $mixValue);
			}
		} else {
			// Create an empty vector
			$this->mData = Vector {};
		}
		// We're done
		return $this;
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Static Constructor //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method constructs a new instance from any traversable data
	 * @access public
	 * @name VariantList::Factory()
	 * @param mixed $tvsSource
	 * @return VariantList
	 * @static
	 */
	public static function Factory(mixed $tvsSource) : VariantList
	{
		// Return the new instance
		return new self($tvsSource);
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Public Static Methods ///////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method constructs a new instance from a sequential array
	 * @access public
	 * @name VariantList::fromArray()
	 * @param array<string, mixed> $arrSource
	 * @return VariantList
	 * @static
	 */
	public static function fromArray(array<mixed> $arrSource) : VariantList
	{
		// Return the new instance
		return new self($arrSource);
	}

	/**
	 * This method constructs a new instance from an existing vector
	 * @access public
	 * @name VariantList::fromVector()
	 * @param HH\Vector<mixed> $vecSource
	 * @return VariantList
	 * @static
	 */
	public static function fromVector(Vector<mixed> $vecSource) : VariantList
	{
		// Return the new instance
		return new self($vecSource);
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Public Methods //////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method adds an element to the vector
	 * @access public
	 * @name VariantList::add()
	 * @param mixed $mixValue
	 * @return VariantList $this
	 */
	public function add(mixed $mixValue) : VariantList
	{
		// Check the type
		if ((is_array($mixValue) && boolval(count(array_filter(array_keys($mixValue), 'is_string'))))
			|| is_object($mixValue)
			|| ($mixValue instanceof HH\Map)) {
			// Set the data into the instance
			$this->mData
				->add(VariantMap::Factory($mixValue));
		} elseif (is_array($mixValue)
			|| ($mixValue instanceof HH\Vector)) {
			// Set the data into the instance
			$this->mData
			 	->add(VariantList::Factory($mixValue));
		} elseif ($mixValue instanceof Variant) {
			// Set the data into the instance
			$this->mData
				->add($mixValue);
		} else {
			// Set the data into the instance
			$this->mData
			 	->add(Variant::Factory($mixValue));
		}
		// We're done
		return $this;
	}

	/**
	 * This method searches the Vector for a key with case-insensitivity and returns the data if found, Variant::Factory(null) elsewise
	 * @access public
	 * @name VariantList::at()
	 * @param int $intKey
	 * @return Variant
	 */
	public function at(int $intKey) : Variant
	{
		// Check for the key
		if ($this->contains($intKey)) {
			// Return the data
			return $this->mData->at($intKey);
		}
		// Return an empty variant
		return Variant::Factory(null);
	}

	/**
	 * This method empties out the vector while returning back refrences
	 * @access public
	 * @name VariantList::clear()
	 * @return VariantList $this
	 */
	public function clear() : VariantList
	{
		// Reset the data, don't use the built-in clear() as it clears all back references as well
		$this->mData = new VariantList();
		// We're done
		return $this;
	}

	/**
	 * This method searches the Vector's keys to determine whether or not a key exists using case-insensitivity
	 * @access public
	 * @name VariantList::contains()
	 * @param int $intKey
	 * @return bool
	 */
	public function contains(int $intKey) : bool
	{
		// Run the built-in
		return $this->mData->containsKey($intKey);
	}

	/**
	 * This is an alias of VariantList::contains()
	 * @access public
	 * @name VariantList::containsKey()
	 * @param int $intKey
	 * @return bool
	 * @see VariantList::contains()
	 */
	public function containsKey(int $intKey) : bool
	{
		// Return the comparison
		return $this->contains($intKey);
	}

	/**
	 * This method returns the number or indices the Vector has
	 * @access public
	 * @name VariantList::count()
	 * @return int
	 */
	public function count() : int
	{
		// Return the size of the VariantList
		return $this->mData->count();
	}

	/**
	 * This method is an alias of VariantList::at()
	 * @access public
	 * @name VariantList::get()
	 * @param int $intKey
	 * @return Variant
	 * @see VariantList::at()
	 */
	public function get(int $intKey) : Variant
	{
		// Return the data
		return $this->at($intKey);
	}

	/**
	 * This method returns an iterator for the data
	 * @access public
	 * @name VariantList::getIterator()
	 * @return KeyedIterator<string, Variant>
	 */
	public function getIterator() : KeyedIterator<int, Variant>
	{
		// Return the iterator
		return $this->mData->getIterator();
	}

	/**
	 * This method groups a VariantList<VariantMap> into a VariantMap<string, VariantList>> indexed by $strMapKey
	 * @access public
	 * @name VariantList::groupedVariantMap()
	 * @param string $strMapKey
	 * @return VariantMap
	 */
	public function groupedVariantMap(string $strMapKey) : VariantMap
	{
		// Create a response map
		$mapReturn = new VariantMap();
		// Iterate over the vector
		foreach ($this->mData->getIterator() as $intIndex => $varValue) {
			// Check for the key in the grid
			if ($varValue->get($strMapKey)->isEmpty() === false) {
				// Check for a key in the map
				if ($mapReturn->contains($varValue->get($strMapKey)) === false) {
					// Create the key
					$mapReturn->set($varValue->get($strMapKey)->toString(), new VariantList());
				}
				// Set the value
				$mapReturn->get($varValue->get($strMapKey)->toString())->add($varValue->getData());
			}
		}
		// Return the response map
		return $mapReturn;
	}

	/**
	 * This method implodes the vector into a string list
	 * @access public
 	 * @name VariantList::implode()
	 * @param string $strDelimiter [,]
	 * @param bool $blnForMySQL [false]
	 * @return string
	 */
	public function implode(string $strDelimiter = ',', bool $blnForMySQL = false) : string
	{
		// Create a temporary vector
		$vecTemp = Vector {};
		// Iterate over the data
		foreach ($this->getIterator() as $intIndex => $varValue) {
			// Check the flag
			if ($blnForMySQL) {
				// Set the data
				$vecTemp
					->add($varValue->toMySqlString());
			} else {
				// Set the data
				$vecTemp
					->add($varValue->toString());
			}
		}
		// Return the imploded vector
		return implode($strDelimiter, $vecTemp->toArray());
	}

	/**
	 * This method implodes the vector with a callback just before data reset
	 * @access public
	 * @name VariantList::implodeCallback()
	 * @param string $strDelimiter [,]
	 * @param callable $fnCallback
	 * @return string
	 */
	public function implodeCallback(string $strDelimiter = ',', callable $fnCallback) : string
	{
		// Localize the data
		$vecTemp = Vector {};
		// Iterate over the data
		foreach ($this->getIterator() as $intIndex => $varValue) {
			// Reset the data after executing the callback
			$vecTemp
				->add($vnCallback($varValue));
		}
		// Return the imploded vector
		return implode($strDelimiter, $vecTemp->toArray());
	}

	/**
	 * This method returns whether or not the data is empty
	 * @access public
	 * @name VariantList::isEmpty()
	 * @return bool
	 */
	public function isEmpty() : bool
	{
		// Return the empty status
		return $this->mData->isEmpty();
	}

	/**
	 * This method removes the last element in the vector and returns it
	 * @access public
	 * @name VariantList::pop()
	 * @return Variant
	 */
	public function pop() : Variant
	{
		// Return the popped value
		return $this->mData->pop();
	}

	/**
	 * This method removes the last element in the vector and returns its real value
	 * @access public
	 * @name VariantList::popReal()
	 * @return mixed
	 */
	public function popReal() : mixed
	{
		// Return the actual value of the popped element
		return $this->mData->pop()->getData();
	}

	/**
	 * This method removes a specified key from the data
	 * @access public
	 * @name VariantList::remove()
	 * @param int $intKey
	 * @return VariantList $this
	 */
	public function remove(int $intKey) : VariantList
	{
		// Remove the key
		$this->mData->removeKey($intKey);
		// We're done
		return $this;
	}

	/**
	 * This method is an alias of VariantList::remove()
	 * @access public
	 * @name VariantList::removeKey()
	 * @param int $intKey
	 * @return VariantList $this
	 * @see VariantList::remove()
	 */
	public function removeKey(int $intKey) : VariantList
	{
		// Return the removal
		return $this->remove($intKey);
	}

	/**
	 * This method reserves the memory for the vecort with $intSize element
	 * @access public
	 * @name VariantList::reserve()
	 * @param int $intSize
	 * @return void
	 */
	public function reserve(int $intSize) : void
	{
		// Reserve the indices
		$this->mData->reserve($intSize);
	}

	/**
	 * This method resizes the Vector, or reserves elements with $mixDefaultValue as the values
	 * @access public
	 * @name VariantList::resize()
	 * @param int $intSize
	 * @param mixed $mixDefaultValue [null]
	 * @return void
	 */
	public function resize(int $intSize, mixed $mixDefaultValue = null) : void
	{
		// Resize the vector
		$this->mData->resize($intSize, $mixDefaultValue);
	}

	/**
	 * This method reverses the order of the indices in the Vector
	 * @access public
	 * @name VariantList::reverse()
	 * @return void
	 */
	public function reverse() : void
	{
		// Reverse the keys
		$this->mData->reverse();
	}

	/**
	 * This method searches the Map for a specified term in the values, if found the index will be returned, -1 elsewise
	 * @access public
	 * @name VariantList::search()
	 * @param string $strTerm
	 * @return string
	 */
	public function search(string $strTerm) : int
	{
		// Return the linear search
		return $this->mData->linearSearch($strTerm);
	}

	/**
	 * This method sets a new key into the instance
	 * @access public
	 * @name VariantList::set()
	 * @param int $intKey
	 * @param mixed $mixValue
	 * @return VariantList $this
	 */
	public function set(int $intKey, mixed $mixValue) : VariantList
	{
		// Check the type
		if ((is_array($mixValue) && boolval(count(array_filter(array_keys($mixValue), 'is_string'))))
			|| is_object($mixValue)
			|| ($mixValue instanceof HH\Map)) {
			// Set the data into the instance
			$this->mData
				->set($intKey, VariantMap::Factory($mixValue));
		} elseif (is_array($mixValue)
			|| ($mixValue instanceof HH\Vector)) {
			// Set the data into the instance
			$this->mData
			 	->set($intKey, VariantList::Factory($mixValue));
		} elseif ($mixValue instanceof Variant) {
			// Set the data into the instance
			$this->mData
				->set($intKey, $mixValue);
		} else {
			// Set the data into the instance
			$this->mData
			 	->set($intKey, Variant::Factory($mixValue));
		}
		// We're done
		return $this;
	}

	/**
	 * This method shuffles the Vector in place
	 * @access public
	 * @name VariantList::shuffle()
	 * @return void
	 */
	public function shuffle() : void
	{
		// Shuffle the data
		$this->mData->shuffle();
	}

	/**
	 * This method splices the data
	 * @access public
	 * @name VariantList::splice()
	 * @param int $intOffset
	 * @param int $intLength [null]
	 * @return void
	 */
	public function splice(int $intOffset, ?int $intLength = null) : void
	{
		// Splice the data
		$this->mData->splice($intOffset, $intLength);
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Converters //////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method returns the data as a sequential array with the values as their original type
	 * @access public
	 * @name VariantList::toArray()
	 * @return array<mixed>
	 */
	public function toArray() : array<mixed>
	{
		// Create the response array
		$arrData = [];
		// Iterate over the data
		foreach ($this->mData->getIterator() as $strKey => $varValue) {
			// Add the key to the response array
			$arrData[$strKey] = $varValue->getData();
		}
		// We're done
		return $arrData;
	}

	/**
	 * This method returns the Vector's keys as an array
	 * @access public
	 * @name VariantList::toKeysArray()
	 * @return array<int>
	 */
	public function toKeysArray() : array<int>
	{
		// Return the keys array
		return $this->mData->toKeysArray();
	}

	/**
	 * This method returns the Vector's keys as a vector
	 * @access public
	 * @name VariantList::toKeysVector()
	 * @return Vector<int>
	 */
	public function toKeysVector() : Vector<int>
	{
		// Return the keys vector
		return new Vector($this->toKeysArray());
	}

	/**
	 * This method returns the Vector's keys as an array with the values in their original type
	 * @access public
	 * @name VariantList::toValuesArray()
	 * @return array<mixed>
	 */
	public function toValuesArray() : array<mixed>
	{
		// Return the values array
		return array_filter($this->mData->toValuesArray(), function(Variant $varValue) {
			// Return the real value
			return $varValue->getData();
		});
	}

	/**
	 * This method returns the the Vector's values as a vector with the values in the original type
	 * @access public
	 * @name VariantList::toValuesVector()
	 * @return HH\Vector<mixed>
	 */
	public function toValuesVector() : Vector<mixed>
	{
		// Return the values vector
		return new Vector($this->toKeysArray());
	}

	/**
	 * This method returns the data as an array with the values in Variant form
	 * @access public
	 * @name VariantList::toVariantArray()
	 * @return array<string, Variant>
	 */
	public function toVariantArray() : array<Variant>
	{
		// Return the data
		return $this->mData->toArray();
	}

	/**
	 * This method returns the Vector's values as an array of Variants
	 * @access public
	 * @name VariantList::toVariantValuesArray()
	 * @return array<Variant>
	 */
	public function toVariantValuesArray() : array<Variant>
	{
		// Return the values array
		return $this->mData->toValuesArray();
	}

	/**
	 * This method returns the Vector's values as a Vector of Variants
	 * @access public
	 * @name VariantList::toVariantValuesVector()
	 * @return HH\Vector<Variant>
	 */
	public function toVariantValuesVector() : Vector<Variant>
	{
		// return the values vector
		return new Vector($this->toVariantValuesArray());
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Getters /////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method retuns the data in its original type
	 * @access public
	 * @name VariantList::getData()
	 * @return HH\Vector<mixed>
	 */
	public function getData() : Vector<mixed>
	{
		// Create the response map
		$vecData = Vector {};
		// Iterate over the data map
		foreach ($this->mData->getIterator() as $varValue) {
			// Reset the data into the new map
			$vecData
				->add($varValue->getData());
		}
		// Return the data
		return $vecData;
	}
}
