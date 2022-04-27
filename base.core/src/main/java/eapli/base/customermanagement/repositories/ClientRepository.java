package eapli.base.customermanagement.repositories;

import eapli.base.customermanagement.domain.Customer;
import eapli.base.customermanagement.domain.Email;
import eapli.framework.domain.repositories.DomainRepository;


public interface ClientRepository extends DomainRepository<Long,Customer> {

    Customer findById(long id);
    Customer findByEmail(Email email);



}
