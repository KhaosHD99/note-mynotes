#include <stdio.h>
#include "contacts.hpp"

    void CContactsManager::init()
    {
    	
    }
    void CContactsManager::uninit()
    {
    	
	}
	
	//static CContactsManager *CContactsManager::get_instance()
   // {
  //  	return (new CContactsManager);
   // }
	 	
	int CContactsManager::get_contact_count()
    {	
    	return curCount;
	}	
	
	int CContactsManager::get_contact_by_index(Contact *contact,	int index)
	{
    	
	}
	
	int CContactsManager::get_contact_by_name(Contact **contact,	const char *szname)
	{
    	
	}
	
	int CContactsManager::get_contact_by_letter(Contact **contact, const char *szletter)
	{
    	
	}
	
	int CContactsManager::get_contact_by_phone(Contact **contact,	const char *szphone)
	{
    	
	}
	
	int CContactsManager::update_contact(Contact *contact)
	{
		
	}

	int CContactsManager::update_contact_by_index(Contact *contact, int index)	
	{
    	
	}
	
	int CContactsManager::add_contact(Contact *contact)
	{
    	
	}
	
	int CContactsManager::add_contact_by_index(Contact *contact, int index)
	{
    	
	}
	
	int CContactsManager::delete_contact_by_index(int index)
	{
    	
	}
	
	int CContactsManager::delete_contact_all()
	{
    	
	}
	
	//sort
	void CContactsManager::sort_by_name()	
	{
    	
	}
	
	void CContactsManager::sort_by_letter()		
	{
    	
	}
	

	int CContactsManager::save_file()
	{
    	
	}

	void CContactsManager::test()
	{
    	printf("\ntest\n");
	}
		

