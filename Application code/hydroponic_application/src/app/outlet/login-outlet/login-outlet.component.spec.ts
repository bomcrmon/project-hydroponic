import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LoginOutletComponent } from './login-outlet.component';

describe('LoginOutletComponent', () => {
  let component: LoginOutletComponent;
  let fixture: ComponentFixture<LoginOutletComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [LoginOutletComponent]
    });
    fixture = TestBed.createComponent(LoginOutletComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
