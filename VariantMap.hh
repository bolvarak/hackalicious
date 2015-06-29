<?hh


class VariantMap extends Variant
{
	//////////////////////////////////////////////////////////////////////////////
	/// Properties //////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////


	/**
	 * This property contains the data for this map
	 * @access protected
	 * @name VariantMap::$mData
	 * @var HH\Map<string, Variant>
	 */
	protected Map<string, Variant> $mData = Map {};

	//////////////////////////////////////////////////////////////////////////////
	/// Constructor /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method sets up the instance with existing data
	 * @access public
	 * @name VariantMap::__construct()
	 * @param KeyedTraversable<Tk, Tv> $ktsSource [null]
	 * @return void
	 */
	public function __construct(?KeyedTraversable<Tk, Tv> $ktsSource = null) : void
	{
		// Check for data
		if (is_null($ktsSource) === false) {
			// Create a new map out of the
			$mapData = new Map($ktsSource);
			// Iterate over the map
			foreach ($mapData->getIterator() as $strKey => $mixValue) {
				// Check the type
				if ((is_array($mixValue) && boolval(count(array_filter(array_keys($mixValue), 'is_string'))))
					|| is_object($mixValue)
					|| ($mixValue instanceof Map)) {
					// Reset the data
					$mapData
						->set($strKey, VariantMap::Factory($mixValue));
				} elseif (is_array($mixValue)
					|| ($mixValue instanceof Vector)) {
					// Reset the data
					$mapData
						->set($strKey, VariantVector::Factory($mixData));
				} else {
					// Reset the data
					$mapData
						->set($strKey, Variant::Factory($mixValue));
				}
			}
			// Set the data into the instance
			$this->mData = $mapData;
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Static Constructor //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method constructs a new instance from any traversable data
	 * @access public
	 * @name VariantMap::Factory()
	 * @param mixed $tvsSource
	 * @return VariantMap
	 * @static
	 */
	public static function Factory(mixed $tvsSource) : VariantMap
	{
		// Check the type
		if (is_object($tvsSource)) {
			// Return the new instance
			return self::fromObject($objSource);
		}
		// Return the new instance
		return new self($tvsSource);
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Public Static Methods ///////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method constructs a new instance from an associative array
	 * @access public
	 * @name VariantMap::fromArray()
	 * @param array<string, mixed> $arrSource
	 * @return VariantMap
	 * @static
	 */
	public static function fromArray(array<string, mixed> $arrSource) : VariantMap
	{
		// Return the new instance
		return new self($arrSource);
	}

	/**
	 * This method constructs a new instance from a Map
	 * @access public
	 * @name VariantMap::fromMap()
	 * @param HH\Map<string, mixed> $mapSource
	 * @return VariantMap
	 * @static
	 */
	public static function fromMap(Map<string, mixed> $mapSource) : VariantMap
	{
		// Return the new instance
		return new self($mapSource);
	}

	/**
	 * This method constructs a new instance from an object
	 * @access public
	 * @name VariantMap::fromObject()
	 * @param object $objSource
	 * @return VariantMap
	 * @static
	 */
	public static function fromObject(object $objSource) : VariantMap
	{
		// Create the array placeholder
		$arrSource = [];
		// Iterate over the object
		foreach ($objSource as $strProperty => $mixValue) {
			// Add the property to the array
			$arrSource[$strProperty] = $mixValue;
		}
		// Return the new instance
		return new self($arrSource);
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Public Methods //////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method searches the Map for a key with case-insensitivity and returns the data if found, Variant::Factory(null) elsewise
	 * @access public
	 * @name VariantMap::at()
	 * @param string $strKey
	 * @return Variant
	 */
	public function at(string $strKey) : Variant
	{
		// Check for the key
		if (($strRealKey = $this->search($strKey)) !== null) {
			// Return the data
			return $this->mData->get($strRealKey);
		}
		// Return an empty variant
		return Variant::Factory(null);
	}

	/**
	 * This method empties out the map while returning back refrences
	 * @access public
	 * @name VariantMap::clear()
	 * @return VariantMap $this
	 */
	public function clear() : VariantMap
	{
		// Reset the data, don't use the built-in clear() as it clears all back references as well
		$this->mData = new VariantMap();
		// We're done
		return $this;
	}

	/**
	 * This method searches the Map's keys to determine whether or not a key exists using case-insensitivity
	 * @access public
	 * @name VariantMap::contains()
	 * @param string $strKey
	 * @return bool
	 */
	public function contains(string $strKey) : bool
	{
		// Run the built-in first
		if ($this->mData->contains($strKey)) {
			// We're done
			return true;
		}
		// Now search the keys using case insensitivity
		return in_array(strtolower($strKey), array_filter($this->toKeysArray(), 'strtolower'));
	}

	/**
	 * This is an alias of VariantMap::contains()
	 * @access public
	 * @name VariantMap::containsKey()
	 * @param string $strKey
	 * @return bool
	 * @see VariantMap::contains()
	 */
	public function containsKey(string $strKey) : bool
	{
		// Return the comparison
		return $this->contains($strKey);
	}

	/**
	 * This method is an alias of VariantMap::at()
	 * @access public
	 * @name VariantMap::get()
	 * @param string $strKey
	 * @return Variant
	 * @see VariantMap::at()
	 */
	public function get(string $strKey) : Variant
	{
		// Return the data
		return $this->at($strKey);
	}

	/**
	 * This method returns an iterator for the data
	 * @access public
	 * @name VariantMap::getIterator()
	 * @return KeyedIterator<string, Variant>
	 */
	public function getIterator() : KeyedIterator<string, Variant>
	{
		// Return the iterator
		return $this->mData->getIterator();
	}

	/**
	 * This method removes a specified key from the data
	 * @access public
	 * @name VariantMap::remove()
	 * @param string $strKey
	 * @return VariantMap $this
	 */
	public function remove(string $strKey) : VariantMap
	{
		// Remove the key
		$this->mData->remove($strKey);
		// We're done
		return $this;
	}

	/**
	 * This method is an alias of VariantMap::remove()
	 * @access public
	 * @name VariantMap::removeKey()
	 * @param string $strKey
	 * @return VariantMap $this
	 * @see VariantMap::remove()
	 */
	public function removeKey(string $strKey) : VariantMap
	{
		// Return the removal
		return $this->remove($strKey);
	}

	/**
	 * This method searches the Map for a specified key with case-insensitivity, if one is found the actual key name is returned, null elsewise
	 * @access public
	 * @name VariantMap::search()
	 * @param string $strKey
	 * @return string
	 */
	public function search(string $strKey) : ?string
	{
		// Check to see if the key exists
		if ($this->mData->contains($strKey)) {
			// We're done
			return $strKey;
		}
		// Iterate over the keys
		foreach ($this->toKeysArray() as $strRealKey) {
			// Check the key
			if (strtolower($strKey) === strtolower($strRealKey)) {
				// We're done
				return $strKey;
			}
		}
		// We're done, no key
		return null;
	}

	/**
	 * This method sets a new key into the instance
	 * @access public
	 * @name VariantMap::set()
	 * @param string $strKey
	 * @param mixed $mixValue
	 * @return VariantMap $this
	 */
	public function set(string $strKey, mixed $mixValue) : VariantMap
	{
		// Check the type
		if ((is_array($mixValue) && boolval(count(array_filter(array_keys($mixValue), 'is_string'))))
			|| is_object($mixValue)
			|| ($mixValue instanceof Map)) {
			// Set the data into the instance
			$this->mData
				->set($strKey, VariantMap::Factory($mixValue));
		} elseif (is_array($mixValue)
			|| ($mixValue instanceof Vector)) {
			// Set the data into the instance
			$this->mData
			 	->set($strKey VariantVector::Factory($mixData));
		} else {
			// Set the data into the instance
			$this->mData
			 	->set($strKey, Variant::Factory($mixValue));
		}
		// We're done
		return $this;
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Converters //////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method returns the data as an associative array with the values as their original type
	 * @access public
	 * @name VariantMap::toArray()
	 * @return array<string, mixed>
	 */
	public function toArray() : array<string, mixed>
	{
		// Create the response array
		$arrData = [];
		// Iterate over the data
		foreach ($this->mData->getIterator() as $strKey => $varValue) {
			// Add the key to the response array
			$arrData[$strKey] => $varValue->getData();
		}
		// We're done
		return $arrData;
	}

	/**
	 * This method returns the Map's keys as an array
	 * @access public
	 * @name VariantMap::toKeysArray()
	 * @return array<string>
	 */
	public function toKeysArray() : array<string>
	{
		// Return the keys array
		return $this->mData->toKeysArray();
	}

	/**
	 * This method returns the Map's keys as a vector
	 * @access public
	 * @name VariantMap::toKeysVector()
	 * @return Vector<string>
	 */
	public function toKeysVector() : Vector<string>
	{
		// Return the keys vector
		return new Vector($this->toKeysArray());
	}

	/**
	 * This method returns the Map's keys as an array with the values in their original type
	 * @access public
	 * @name VariantMap::toValuesArray()
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
	 * This method returns the the Map's values as a vector with the values in the original type
	 * @access public
	 * @name VariantMap::toValuesVector()
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
	 * @name VariantMap::toVariantArray()
	 * @return array<string, Variant>
	 */
	public function toVariantArray() : array<string, Variant>
	{
		// Return the data
		return $this->mData->toArray();
	}

	/**
	 * This method returns the Map's values as an array of Variants
	 * @access public
	 * @name VariantMap::toVariantValuesArray()
	 * @return array<Variant>
	 */
	public function toVariantValuesArray() : array<Variant>
	{
		// Return the values array
		return $this->mData->toValuesArray();
	}

	/**
	 * This method returns the Map's values as a Vector of Variants
	 * @access public
	 * @name VariantMap::toVariantValuesVector()
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
	 * @name VariantMap::getData()
	 * @return HH\Map<string, mixed>
	 */
	public function getData() : Map<string, mixed>
	{
		// Create the response map
		$mapData = Map {};
		// Iterate over the data map
		foreach ($this->mData->getIterator() as $strKey => $varValue) {
			// Reset the data into the new map
			$mapData
				->set($strKey, $varValue->getData());
		}
		// Return the data
		return $mapData;
	}
}
