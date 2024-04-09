import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SprinkerComponent } from './sprinker.component';

describe('SprinkerComponent', () => {
  let component: SprinkerComponent;
  let fixture: ComponentFixture<SprinkerComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [SprinkerComponent]
    });
    fixture = TestBed.createComponent(SprinkerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
